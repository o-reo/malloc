/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:04:51 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 18:41:24 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Init a zone
*/

t_zone			*zone_new(void *header_location, size_t size)
{
	t_zone	*zone;
	int		i;
	char	*first_byte;
	char	*last_byte;

	zone = (t_zone *)header_location;
	zone->data = memory_map(NULL, size);
	zone->size = size;
	zone->next = NULL;
	first_byte = zone_get_first_byte(zone);
	last_byte = zone_get_last_byte(zone);
	i = divide_ceil(size, 8 * ALIGNMENT);
	while (i-- >= 0)
	{
		first_byte[i] = 0;
		last_byte[i] = 0;
	}
	return (zone);
}

enum e_bool		zone_chunk_forget(t_zone *zone, void *address)
{
	size_t	i;
	int64_t *first_bytes;
	int64_t *last_bytes;

	first_bytes = (int64_t*)zone_get_first_byte(zone);
	last_bytes = (int64_t*)zone_get_last_byte(zone);
	i = divide_ceil(address - zone->data, ALIGNMENT);
	if (((first_bytes[i / 64] >> (i % 64)) & 1L) != 1)
		return (e_false);
	while (i > 0 && ((first_bytes[i / 64] >> (i % 64)) & 1L) == 0 &&
		   	((last_bytes[i / 64] >> (i % 64) & 1L) == 0))
		i--;
	first_bytes[i / 64] ^= 1L << (i % 64);
	while (((last_bytes[i / 64] >> (i % 64)) & 1L) == 0)
		i++;
	last_bytes[i / 64] ^= 1L << (i % 64);
	return (e_true);
}

/*
** Record a chunk in the byte array
** @return the new chunk or NULL if zone has no sufficient contiguous space
*/

void			*zone_chunk_register(t_zone *zone, size_t first, size_t last)
{
	int64_t	*first_bytes;
	int64_t	*last_bytes;

	last -= last > 0 ? 1 : 0;
	first_bytes = (int64_t*)zone_get_first_byte(zone);
	last_bytes = (int64_t*)zone_get_last_byte(zone);
	first_bytes[first / 64] |= (1L << (first % 64));
	last_bytes[last / 64] |= (1L << (last % 64));
	return (zone->data + ALIGNMENT * first);
}

/*
** Goes through the byte arrays to get a gap with the good size
** @return the available zone byte
*/

void			*zone_chunk_create(t_zone *zone, size_t size)
{
	size_t		i;
	int64_t		*first_byte;
	int64_t		*last_byte;
	size_t		first_index;
	size_t		current_size;

	first_byte = (int64_t*)zone_get_first_byte(zone);
	last_byte = (int64_t*)zone_get_last_byte(zone);
	current_size = divide_ceil(zone->size, ALIGNMENT);
	i = 0;
	while (i < current_size)
	{
		while (i < current_size && 
				(((last_byte[i / 64] >> (i % 64)) & 1L) == 0))
			i++;
		if (i >= current_size && size <= zone->size)
			return (zone_chunk_register(zone, 0, divide_ceil(size, ALIGNMENT)));
		first_index = ++i;
		while (i < current_size && (((first_byte[i / 64] >> (i % 64)) & 1L)
					== 0))
			i++;
		if (i >= (divide_ceil(size, ALIGNMENT) + first_index))
			return (zone_chunk_register(zone, first_index, first_index +
					divide_ceil(size, ALIGNMENT)));
	}
	return (NULL);
}
