/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone_utils3.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 16:49:44 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 18:23:22 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

size_t		zone_get_available_size(t_zone *zone, void *address)
{
	size_t		i;
	uint32_t	*bytes;
	size_t		first;

	bytes = (uint32_t*)zone_get_first_byte(zone);
	first = divide_ceil(address - zone->data, zone_quantum(zone->size));
	if (((bytes[first / 32] >> (first % 32)) & 1L) != 1)
		return (0);
	i = first + 1;
	while (i < 8 * zone_bytes_size(zone->size) && 
			((bytes[i / 32] >> (i % 32)) & 1L) != 1)
		i++;
	return ((i - first) * zone_quantum(zone->size));
}

enum e_bool	zone_realloc(t_zone *zone, void *address, size_t size)
{
	size_t	available;
	size_t	first;

	available = zone_get_available_size(zone, address);
	first = divide_ceil(address - zone->data, zone_quantum(zone->size));
	if (available >= size)
	{
		zone_chunk_forget(zone, address);		
		zone_chunk_register(zone, first, first + 
				divide_ceil(size, zone_quantum(zone->size)));
		return (e_true);		
	}
	return (e_false);
}

size_t		zone_chunk_size(t_zone *zone, void *address)
{
	size_t		last;
	size_t		first;
	uint32_t	*bytes;

	first = divide_ceil(address - zone->data, zone_quantum(zone->size));
	bytes = (uint32_t*)zone_get_first_byte(zone);
	last = first + 1;
	while (last < 8 * zone_bytes_size(zone->size) && 
			((bytes[last / 32] >> (last % 32)) & 1L) != 1)
		last++;
	return (last - first);
}

void		zone_chunk_copy(t_zone *zone, void *src, void *dest)
{
	size_t	i;
	size_t max;

	i = 0;
	max =  zone->size >= zone_large ? zone->size : zone_chunk_size(zone, src);
	// write_num(zone->size);
	while (i < max)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
}
