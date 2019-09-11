/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   registry.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 12:03:17 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 18:32:29 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void		*g_registries = NULL;

/*
** Allocates a registry page 
** first bytes of registry is the pointer to the next
*/
void		registry_init(void)
{
	void		*registry_memory;
	void		*limit;

	if (g_registries != NULL)
		return ;
	registry_memory = memory_map(NULL, REGISTRY_SIZE);
	g_registries = registry_memory;
	((t_registry*)g_registries)->next = NULL;
	limit = registry_memory + REGISTRY_SIZE;
	while (registry_memory < limit)
	{
		((char*)registry_memory)[0] = 0; 
		registry_memory++;	
	}
}

/*
** Appends a new registry to the list
*/
void		*registry_append(void)
{
	t_registry	*last_registry;
	void		*registry_memory;
	void		*limit;
	void		*i_registry;

	last_registry = g_registries;
	while (last_registry->next)
		last_registry = last_registry->next;
	registry_memory = memory_map(last_registry + REGISTRY_SIZE, REGISTRY_SIZE);
	last_registry->next = registry_memory;
	((t_registry *)registry_memory)->next = NULL;
	limit = registry_memory + REGISTRY_SIZE;
	i_registry = registry_memory + sizeof(t_registry);
	while (i_registry < limit)
	{
		((char*)i_registry)[0] = 0; 
		i_registry++;	
	}
	return (registry_memory);
}

/*
 * Registry
*/
t_zone		*registry_zone_add(size_t size)
{
	void		*prev_address;
	void		*address;
	void		*reg;
	size_t		gap;
	t_zone		*zone;

	reg = g_registries;
	while (reg)
	{
		prev_address = NULL;
		address = reg + sizeof(t_registry);
		while (address)
		{
			zone = (t_zone*)address;
			// must create first zone 
			if (zone->data == NULL)
				return (zone_new(address, size));	
			gap = zone->next ? (void*)(zone->next) - address : 
				reg + REGISTRY_SIZE - (address + zone_size(zone->size));
			if (gap >= zone_size(size))
			{
				zone = zone_new(address + zone_size(zone->size), size);
				if (prev_address)
					((t_zone*)prev_address)->next = zone;
				return (zone);
			}
			prev_address = address;
			// go to next available zone
			address = (void*)(zone->next);
		}
		reg = ((t_registry*)reg)->next;
	}
	reg = registry_append();
	return (zone_new(reg + sizeof(t_registry), size));
}

t_zone		*registry_zone_find(void *address)
{
	t_zone	*zone;
	void	*reg;

	reg = g_registries;
	while (reg)
	{
		zone = (t_zone*)(reg + sizeof(t_registry)); 
		while (zone)
		{
			if (address >= zone->data && 
				address < (zone->data + zone->size))
				return (zone);		
			zone = zone->next;
		}
		reg = ((t_registry*)reg)->next;
	}
	return (NULL);
}

void		*registry_zone_create_chunk(size_t size)
{
	void	*chunk;
	void	*reg;
	t_zone	*zone;
	size_t	zone_size;

	chunk = NULL;
	reg = g_registries;
	zone_size = size > chunk_tiny_max ? zone_small : zone_tiny;  
	while (reg && !chunk)
	{	
		zone = (t_zone*)(reg + sizeof(t_registry));
		while (zone && zone->data && !(chunk = zone_chunk_create(zone, size)))
			zone = zone->next;
		reg = ((t_registry*)reg)->next;
	}
	if (!chunk) {
		chunk = zone_chunk_create(registry_zone_add(zone_size), size);
	}
	return (chunk);
}

