/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:21:39 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 14:28:34 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static int	test_zone(void)
{
	t_zone		*zone;
	void		*chunk;

	write(0, "~----------------------------~\n", 31);
	write(0, "~-------Malloc Testing-------~\n", 31);

	registry_init();
	zone = registry_zone_add(zone_tiny);	
	
	zone_chunk_create(zone, 16);
	chunk = zone_chunk_create(zone, 32);
	zone_chunk_create(zone, 10);
	zone_chunk_forget(zone, chunk);
	zone_chunk_create(zone, 48);
	zone_print(zone);
	return (0);
}

int		main()
{
	test_zone();
    return (0);
}
