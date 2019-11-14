/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   registry.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 12:03:17 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 15:13:37 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Allocates a registry page 
** first bytes of registry is the pointer to the next
*/
void registry_init(void)
{
	void *registry_memory;

	if (g_registries != NULL)
		return;
	registry_memory = memory_map(NULL, REGISTRY_SIZE);
	g_registries = registry_memory;
	ft_bzero(registry_memory, REGISTRY_SIZE);
}

/*
** Appends a new registry to the list
*/
void *registry_append(void)
{
	t_registry *last_registry;
	void *registry_memory;

	last_registry = g_registries;
	while (last_registry->next)
		last_registry = last_registry->next;
	registry_memory = memory_map(last_registry + REGISTRY_SIZE, REGISTRY_SIZE);
	ft_bzero(registry_memory, REGISTRY_SIZE);
	last_registry->next = registry_memory;
	return (registry_memory);
}

/*
 * Registry
*/
t_zone *registry_zone_add(size_t size)
{
	void *address;
	void *reg;
	size_t gap;
	t_zone *zone;

	reg = g_registries;
	while (reg)
	{
		address = reg + memory_align_size(sizeof(t_registry));
		while (address)
		{
			zone = (t_zone *)address;
			if (zone->data == NULL &&
				zone_head_size(zone->size) < REGISTRY_SIZE)
				return (zone_new(address, size));
			gap = zone->next ? (void *)(zone->next) -
								   address - zone_head_size(zone->size)
							 : reg + REGISTRY_SIZE - address - zone_head_size(zone->size);
			if (gap >= zone_head_size(size))
			{
				zone = zone_new(address + zone_head_size(zone->size), size);
				((t_zone *)address)->next = zone;
				return (zone);
			}
			address = (void *)(zone->next);
		}
		reg = ((t_registry *)reg)->next;
	}
	reg = registry_append();
	return (zone_new(reg + memory_align_size(sizeof(t_registry)), size));
}

t_zone *registry_zone_find(void *address)
{
	t_zone *zone;
	void *reg;

	reg = g_registries;
	while (reg)
	{
		zone = (t_zone *)(reg + memory_align_size(sizeof(t_registry)));
		while (zone)
		{
			if (address >= zone->data &&
				address < (zone->data + zone->size))
				return (zone);
			zone = zone->next;
		}
		reg = ((t_registry *)reg)->next;
	}
	return (NULL);
}

void *registry_zone_create_chunk(size_t size)
{
	void *chunk;
	void *reg;
	t_zone *zone;
	size_t zone_size;

	chunk = NULL;
	reg = g_registries;
	zone_size = size > chunk_tiny_max ? zone_small : zone_tiny;
	while (reg && !chunk)
	{
		zone = (t_zone *)(reg + memory_align_size(sizeof(t_registry)));
		while (zone && !(chunk = zone_chunk_create(zone, size)))
			zone = zone->next;
		reg = ((t_registry *)reg)->next;
	}
	if (!chunk)
	{
		chunk = zone_chunk_create(registry_zone_add(zone_size), size);
	}
	return (chunk);
}

void *registry_zone_large(size_t size)
{
	t_zone *zone;

	zone = registry_zone_add(size + memory_align_size(sizeof(t_zone)));
	return (zone->data);
}

void registry_chunk_forget(void *address)
{
	t_zone *zone;

	if (!(zone = registry_zone_find(address)) ||
		zone_get_available_size(zone, address) == 0)
	{
		return;
	}
	// FREE ZONE IF EMPTY?
	if (zone->size >= zone_large || zone_is_empty(zone))
	{
		zone_free(zone);
		registry_free_if_empty();
	}
}
