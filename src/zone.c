/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:04:51 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 17:47:03 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Init a zone and map its data
*/

t_zone			*zone_new(void *header_location, size_t size)
{
	t_zone		*zone;

	zone = (t_zone *)header_location;
	if (size < zone_large)
		ft_bzero(zone, zone_head_size(zone->size));
	zone->data = memory_map(NULL, size);
	zone->size = size;
	zone->next = NULL;
	return (zone);
}

/*
** Set first and last markers to 0
*/

enum e_bool		zone_chunk_forget(t_zone *zone, void *address)
{
	size_t	i;
	uint32_t *first_bytes;
	uint32_t *last_bytes;

	first_bytes = (uint32_t*)zone_get_first_byte(zone);
	last_bytes = (uint32_t*)zone_get_last_byte(zone);
	i = divide_ceil(address - zone->data, zone_quantum(zone->size));
	if (((first_bytes[i / 32] >> (i % 32)) & 1L) != 1)
		return (e_false);
	while (i > 0 && ((first_bytes[i / 32] >> (i % 32)) & 1L) == 0 &&
		   	((last_bytes[i / 32] >> (i % 32) & 1L) == 0))
		i--;
	first_bytes[i / 32] ^= 1L << (i % 32);
	while (((last_bytes[i / 32] >> (i % 32)) & 1L) == 0)
		i++;
	last_bytes[i / 32] ^= 1L << (i % 32);
	return (e_true);
}

/*
** Record a chunk in the byte array
** @return the new chunk or NULL if zone has no sufficient contiguous space
*/

void			*zone_chunk_register(t_zone *zone, size_t first, size_t last)
{
	uint32_t	*first_bytes;
	uint32_t	*last_bytes;

	last -= last > 0 ? 1 : 0;
	first_bytes = (uint32_t*)zone_get_first_byte(zone);
	last_bytes = (uint32_t*)zone_get_last_byte(zone);
	first_bytes[first / 32] |= (1L << (first % 32));
	last_bytes[last / 32] |= (1L << (last % 32));
	return (zone->data + zone_quantum(zone->size) * first);
}

/*
** Explore the zone and create a chunk when there is a sufficient gap
** @return the recorded chunk
*/

void			*zone_chunk_create(t_zone *zone, size_t size)
{
	size_t		i;
	uint32_t	*first_byte;
	uint32_t	*last_byte;
	size_t		prev_i;
	size_t		current_size;

	if (size > chunk_tiny_max && zone->size != zone_small)
		return (NULL);
	first_byte = (uint32_t*)zone_get_first_byte(zone);
	last_byte = (uint32_t*)zone_get_last_byte(zone);
	current_size = 8 * zone_bytes_size(zone->size);
	i = 0;
	prev_i = 0;
	while (i < current_size)
	{
		while (i < current_size && 
				(((first_byte[i / 32] >> (i % 32)) & 1L) == 0))
			i++;
		if ((i - prev_i) >= divide_ceil(size, zone_quantum(zone->size)))
			return (zone_chunk_register(zone, prev_i, 
						prev_i + divide_ceil(size, zone_quantum(zone->size))));
		while (i < current_size && (((last_byte[i / 32] >> (i % 32)) & 1L)
					== 0))
			i++;
		prev_i = ++i;
	}
	return (NULL);
}
