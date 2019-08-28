/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:04:51 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/28 18:42:53 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Returns the length of the expected bit array
*/
static int	zone_get_array_len(const size_t size)
{
	return (size / 8 * ALIGNMENT_IN_BYTES);
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
	while (i-- > 0)
	{
		first_byte[i] = 0;
		last_byte[i] = 0;
	}
	return (zone);
}


void	zone_print(t_zone *zone)
{
	int		i;
	int16_t *first_bytes;
	
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
	i = 0;
	while (i < zone_get_array_len(zone->size))
	{
		if (first_bytes[i / 16] << (i % 16) == 1)
			write_ptr(zone->data + i * ALIGNMENT_IN_BYTES);
		i++;
	}
}

size_t			zone_browse_last_bits(char byte)
{
	size_t		size;
	int			bit;

	bit = 0;
	while (bit < 4)
	{
		if ((byte & 0b10000000) == 0)
			size++;
		else
			size = 0;
		byte <<= 1;
		bit++;
	}
	return (size);
}

/*
** Gets available size, if the last bit is 0 the value is negative
*/
size_t			zone_browse_first_bits(char byte)
{
	size_t		size;
	int			bit;

	bit = 0;
	while (bit < 4)
	{
		if ((byte & 1) == 0) 
			size++;
		else
			size = 0;
		byte >>= 1;
		bit++;
	}
	return (size);
}

/*
** Goes through the byte arrays to get a gap with the good size
** @return the available zone byte
*/
void		*zone_get_available_space(t_zone *zone, size_t size)
{
	size_t		i;
	int16_t		*first_byte;
	int16_t		*last_byte;
	size_t		first_index;
	size_t		current_size;

	first_byte = (int16_t*)zone_get_first_byte(zone);
	last_byte = (int16_t*)zone_get_last_byte(zone);
	current_size = 8 * zone_get_array_len(zone->size);
	i = 0;
	// Goes bit per bit
	while (i < current_size)
	{
		// iterates until we have a 0
		while (((first_byte[i / 16] >> (i % 16)) & 1) == 1)
			i++;
		first_index = i;
		// iterates until we have a 1 
		while (((last_byte[i / 16] >> (i % 16)) & 1) == 0)
			i++;
		if ((i - first_index) >= size)
		   return (zone->data + ALIGNMENT_IN_BYTES * first_index);	
	}
	return (NULL);	
}

/*
** Record a chunk in the byte array
** @return the new chunk or NULL if zone has no sufficient contiguous space
*/
void			*zone_chunk_create(t_zone *zone, size_t size)
{
	(void)size;
	(void)zone;
	return (NULL);
}
