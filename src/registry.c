/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   registry.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 12:03:17 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/02 15:27:02 by eruaud      ###    #+. /#+    ###.fr     */
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

	registry_memory = memory_map(NULL, REGISTRY_SIZE);
	g_registries = registry_memory;
	((t_registry*)g_registries)->next = NULL;
}

/*
** Appends a new registry to the list
*/
void		registry_append(void)
{
	t_registry	*last_registry;
	void		*registry_memory;

	last_registry = g_registries;
	while (last_registry->next)
	{
		last_registry = last_registry->next;
	}
	registry_memory = memory_map(last_registry + REGISTRY_SIZE, REGISTRY_SIZE);
	last_registry->next = registry_memory;
	((t_registry *)registry_memory)->next = NULL;
}

/*
 * Registry
*/
t_zone		*registry_zone_add(size_t size)
{
	t_zone	*zone;

	zone = zone_new(g_registries + sizeof(t_registry), size);
	return (zone);
}
