/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone_utils2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/11 16:39:20 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 15:41:27 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

size_t zone_quantum(size_t size)
{
	return (size > zone_tiny ? QUANTUM_SMALL : QUANTUM_TINY);
}

/*
** Number of bytes dedicated to memory mapping 
*/
size_t zone_bytes_size(size_t size)
{
	return (divide_ceil(size, zone_quantum(size) * 8));
}

/*
** Total size of zone metadata
*/
size_t zone_head_size(t_zone *zone)
{
	if (zone->id == zone_large_id)
		return (memory_align_size(sizeof(t_zone)));
	return (memory_align_size(sizeof(t_zone)) + 2 * zone_bytes_size(zone->size));
}

enum e_bool zone_is_empty(t_zone *zone)
{
	size_t max;
	size_t index;
	uint32_t *bytes;

	if (zone->id == zone_large_id)
		return (e_false);
	bytes = (uint32_t *)zone_get_first_byte(zone);
	max = zone_bytes_size(zone->size);
	index = 0;
	while (index < max && bytes[index / 32] == 0)
		index++;
	if (bytes[index] != 0)
		return (e_false);
	return (e_true);
}

void zone_free(t_zone *zone)
{
	if (((t_registry *)g_registries)->next == NULL && zone->next == NULL)
	{
		return;
	}
	memory_unmap(zone->data, zone->size);
	zone->data = NULL;
	zone->size = zone_empty;
	zone->id = zone_empty_id;
}
