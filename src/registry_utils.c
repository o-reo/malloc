/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   registry_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 15:41:16 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 11:26:33 by eruaud      ###    #+. /#+    ###.fr     */
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
		write(0, "registry:\n", 10);
		write_ptr(reg);
		write(0, "\n", 1);
		zone = (t_zone*)(reg + sizeof(t_registry));
		while (zone)
		{
			zone_print(zone);
			zone = zone->next;
		}
		reg = ((t_registry*)reg)->next;
	}
}

void		registry_reset(void)
{
	void	*reg;
	void	*limit;
	void	*memory;
	void	*to_free;

	reg = (t_registry*)g_registries;

	while (reg)
	{
		memory = reg;
		limit = reg + REGISTRY_SIZE;
		while (memory++ < limit)
			((char*)memory)[0] = 0;	
		to_free = reg;
		reg = ((t_registry*)reg)->next;
		munmap(to_free, REGISTRY_SIZE);
	}
	g_registries = NULL;
}
