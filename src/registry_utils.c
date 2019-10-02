/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   registry_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 15:41:16 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 11:48:55 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void		show_alloc_mem(void)
{
	void	*reg;
	t_zone	*zone;

	reg = g_registries;
	while (reg)
	{
		write(1, "registry:\n", 10);
		write_ptr(reg);
		write(1, "\n", 1);
		zone = (t_zone*)(reg + memory_align_size(sizeof(t_registry)));
		while (zone)
		{
			zone_print(zone);
			zone = zone->next;
		}
		reg = ((t_registry*)reg)->next;
	}
}

enum e_bool	registry_is_empty(t_registry *registry)
{
	t_zone	*zone;
	
	zone = (t_zone*)(registry + memory_align_size(sizeof(t_registry))); 	
	while (zone->next && zone->data == NULL)
		zone = zone->next;
	if (zone->data != NULL)
		return (e_false);
	return (e_true);	
}

void		registry_free_if_empty(void)
{
	t_registry	*reg;
	t_registry	*prev_reg;

	reg = g_registries;
	if (reg->next == NULL)
		return;
	prev_reg = NULL;
	while (reg)
	{
		if (registry_is_empty(reg))
		{
			if (prev_reg == NULL)
				g_registries = NULL;
			else
				prev_reg->next = reg->next;
			memory_unmap(reg, REGISTRY_SIZE);
			reg = prev_reg;	
		}
		prev_reg = reg;
		reg = reg ? reg->next : NULL;
	}
}

void		registry_reset(void)
{
	void	*reg;
	void	*to_free;
	t_zone	*zone;

	reg = (t_registry*)g_registries;

	while (reg)
	{
		to_free = reg;
		zone = (t_zone*)(reg + memory_align_size(sizeof(t_registry)));
		while (zone)
		{
			memory_unmap(zone->data, zone->size);
			zone = zone->next;
		}
		reg = ((t_registry*)reg)->next;
		memory_unmap(to_free, REGISTRY_SIZE);
	}
	g_registries = NULL;
}
