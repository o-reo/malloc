/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:04:51 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 14:28:15 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Returns the length of the expected bit array
*/
static size_t	zone_get_array_len(const size_t size)
{
	return (size / ALIGNMENT_IN_BYTES);
}

/*
** Returns the first byte word at the specified index
*/
static void	*zone_get_last_byte(t_zone *zone)
{
	return (zone + sizeof(t_zone) + zone_get_array_len(zone->size));
}

/*
** Returns the first byte word at the specified index
*/
static void	*zone_get_first_byte(t_zone *zone)
{
	return (zone + sizeof(t_zone));
}

/*
** Init a zone
*/
t_zone	*zone_new(void *header_location, size_t size)
{
	t_zone	*zone;
	int		i;
	char	*first_byte;
	char	*last_byte;

	zone = (t_zone *)header_location;
	zone->data = memory_map(NULL, size);
	zone->size = size;
	first_byte = zone_get_first_byte(zone);
	last_byte = zone_get_last_byte(zone);
	i = zone_get_array_len(size);
	while (i-- >= 0)
	{
		first_byte[i] = 0;
		last_byte[i] = 0;
	}
	return (zone);
}

enum e_bool	zone_check_range(t_zone *zone, void *address)
{
	return (address >= zone->data && address < (zone->data + zone->size));
}

void			zone_print_mask(t_zone *zone)
{
	size_t	i;
	int64_t	*first_bytes;
	int64_t	*last_bytes;

	first_bytes = (int64_t*)zone_get_first_byte(zone);
	i = 0;
	while (i < zone_get_array_len(zone->size))
	{
		if ((first_bytes[i / 64] >> i % 64) & 1)
			write(0, "1", 1);
		else
			write(0, "0", 1);
		i++;
	}
	last_bytes = (int64_t*)zone_get_last_byte(zone);
	i = 0;
	while (i < zone_get_array_len(zone->size))
	{
		if ((last_bytes[i / 64] >> i % 64) & 1)
			write(0, "1", 1);
		else
			write(0, "0", 1);
		i++;
	}
	write(0, "\n", 1);
}

void		zone_chunk_forget(t_zone *zone, void *address)
{
	size_t	i;
	int64_t *first_bytes;
	int64_t *last_bytes;


	first_bytes = (int64_t*)zone_get_first_byte(zone);
	last_bytes = (int64_t*)zone_get_last_byte(zone);

	i = ((((size_t)address - (size_t)zone->data)) % ALIGNMENT_IN_BYTES != 0)
	   	+ (size_t)(address - zone->data) / ALIGNMENT_IN_BYTES;
	while ((i > 0 && (first_bytes[i / 64] >> (i % 64)) & 1) == 0)
		i--;
	first_bytes[i / 64] ^= 1 << (i % 64);	
	while (((last_bytes[i / 64] >> (i % 64)) & 1) == 0)
		i++;
	last_bytes[i / 64] ^= 1 << (i % 64);	
}


void	zone_print(t_zone *zone)
{
	size_t	i;
	int64_t *first_bytes;
	int64_t *last_bytes;
	int64_t	first_byte;

	if (zone->size <= zone_tiny)
	{
		write(0, "TINY : ", 7);
	}
	else if (zone->size <= zone_small)
	{
		write(0, "SMALL : ", 8);
	}
	else
	{
		write(0, "LARGE : ", 8);
	}
	write_ptr(zone->data);
	write(0, "\n", 2);
	first_bytes = zone_get_first_byte(zone);
	last_bytes = zone_get_last_byte(zone);
	i = 0;
	first_byte = i;
	while (i < zone_get_array_len(zone->size))
	{
		if ((first_bytes[i / 64] >> (i % 64)) & 1)
		{
			first_byte = i;
			write_ptr(zone->data + i * ALIGNMENT_IN_BYTES);
			write(0, " - ", 3);
		}
		if ((last_bytes[i / 64] >> (i % 64)) & 1)
		{
			write_ptr(zone->data + (i + 1) * ALIGNMENT_IN_BYTES - 1);	
			write(0, ": ", 2);
			write_num((i - first_byte + 1) * ALIGNMENT_IN_BYTES);
			write(0, " octets\n", 8);
		}
		i++;
	}
	write(0, "\n", 2);
}


/*
** Record a chunk in the byte array
** @return the new chunk or NULL if zone has no sufficient contiguous space
*/
void			*zone_chunk_register(t_zone *zone, size_t first, size_t last)
{
	int64_t	*first_bytes;
	int64_t	*last_bytes;

	last--;
	first_bytes = (int64_t*)zone_get_first_byte(zone);
	last_bytes = (int64_t*)zone_get_last_byte(zone);
	first_bytes[first / 64] |= (1 << (first % 64)); 
	last_bytes[last / 64] |= (1 << (last % 64)); 
	return (NULL);
}

static size_t memory_align_index(size_t index)
{
	return ((index % ALIGNMENT_IN_BYTES != 0) + index / ALIGNMENT_IN_BYTES);
}


/*
** Goes through the byte arrays to get a gap with the good size
** @return the available zone byte
*/
void		*zone_chunk_create(t_zone *zone, size_t size)
{
	size_t		i;
	int64_t		*first_byte;
	int64_t		*last_byte;
	size_t		first_index;
	size_t		current_size;

	first_byte = (int64_t*)zone_get_first_byte(zone);
	last_byte = (int64_t*)zone_get_last_byte(zone);
	current_size = zone_get_array_len(zone->size);
	i = 0;
	while (i < current_size)
	{
		while (i < current_size && (((last_byte[i / 64] >> (i % 64)) & 1) == 0))
			i++;
		if (i >= current_size && size <= zone->size)
		{
			zone_chunk_register(zone, 0, memory_align_index(size));
			return (zone->data);	
		}
		i++;
		first_index = i;
		while (i < current_size && (((first_byte[i / 64] >> (i % 64)) & 1) == 0))
			i++;
		if (i >= ((size % ALIGNMENT_IN_BYTES != 0) + size / ALIGNMENT_IN_BYTES + first_index))
		{
			zone_chunk_register(zone, first_index, first_index + 
					size / ALIGNMENT_IN_BYTES + ((size % ALIGNMENT_IN_BYTES) != 0));
			return (zone->data + 16 * first_index);
		}
	}
	return (NULL);	
}
