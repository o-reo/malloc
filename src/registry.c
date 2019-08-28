/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   registry.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 12:03:17 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/28 18:44:08 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Allocates a registry page 
** first bytes of registry is the pointer to the next
*/
void		registry_init()
{
	void		*registry_memory;

	registry_memory = memory_map(NULL, REGISTRY_SIZE);
	g_registries = (t_registry *)registry_memory;
	g_registries->next = NULL;
}

/*
** Appends a new registry to the list
*/
void		registry_append()
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
