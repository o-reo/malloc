/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:21:39 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/22 17:47:49 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static int	test_zone(void)
{
	t_zone	*zone;
	t_chunk	*new_chunk1;
	t_chunk	*new_chunk2;
	t_chunk	*new_chunk3;
	
	write(0, "~----------------------------~\n", 31);
	write(0, "~-------Malloc Testing-------~\n", 31);
	zone = zone_new(NULL, zone_tiny);
	
	new_chunk1 = zone_chunk_create(zone, zone_tiny / 4);
	zone_print(zone);
	
	new_chunk2 = zone_chunk_create(zone, zone_tiny / 4);
	zone_print(zone);
	
	new_chunk3 = zone_chunk_create(zone, zone_tiny / 4);
	zone_print(zone);

	zone_chunk_delete(zone, new_chunk2);	
	new_chunk2 = zone_chunk_create(zone, zone_tiny / 4);
	zone_print(zone);
	
	zone_chunk_delete(zone, new_chunk1);
	zone_chunk_delete(zone, new_chunk2);
	zone_chunk_delete(zone, new_chunk3);
	
	zone_print(zone);
	return (0);
}

int		main()
{
	test_zone();
    return (0);
}
