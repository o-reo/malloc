/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/06 17:31:45 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 16:43:31 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Returns the first byte word at the specified index
*/

void			*zone_get_last_byte(t_zone *zone)
{
	return (zone + sizeof(t_zone) + zone->size / (8 * ALIGNMENT));
}

/*
** Returns the first byte word at the specified index
*/

void			*zone_get_first_byte(t_zone *zone)
{
	return (zone + sizeof(t_zone));
}

void			zone_print_mask(t_zone *zone)
{
	size_t	i;
	int64_t	*first_bytes;
	int64_t	*last_bytes;

	first_bytes = (int64_t*)zone_get_first_byte(zone);
	i = 0;
	while (i < zone->size / ALIGNMENT)
	{
		if ((first_bytes[i / 64] >> i % 64) & 1)
			write(0, "1", 1);
		else
			write(0, "0", 1);
		i++;
	}
	write(0, "\n", 1);
	last_bytes = (int64_t*)zone_get_last_byte(zone);
	i = 0;
	while (i < zone->size / ALIGNMENT)
	{
		(last_bytes[i / 64] >> i % 64) & 1 ? write(0, "1", 1) :
			write(0, "0", 1);
		i++;
	}
	write(0, "\n", 1);
}

static size_t	zone_print_chunk(t_zone *zone, int64_t *first_bytes,
		int64_t *last_bytes, size_t i)
{
	size_t	first_byte;
	size_t	current_size;

	current_size = divide_ceil(zone->size, ALIGNMENT);
	first_byte = 0;
	while (((first_bytes[i / 64] >> (i % 64)) & 1L) == 0 
			&& i < current_size)
		i++;
	first_byte = i;
	while (((last_bytes[i / 64] >> (i % 64)) & 1L) == 0 
			&& i < current_size)
		i++;
	if (i >= current_size)
		return (current_size);
	write_ptr(zone->data + first_byte * ALIGNMENT);
	write(0, " - ", 3);
	write_ptr(zone->data + (i + 1) * ALIGNMENT - 1);
	write(0, ": ", 2);
	write_num((i - first_byte + 1) * ALIGNMENT);
	write(0, " octets\n", 8);
	return (i + 1);
}

void			zone_print(t_zone *zone)
{
	size_t	i;
	int64_t *first_bytes;
	int64_t *last_bytes;

	if (zone->size <= zone_tiny)
		write(0, "TINY : ", 7);
	else if (zone->size <= zone_small)
		write(0, "SMALL : ", 8);
	else
		write(0, "LARGE : ", 8);
	write_ptr(zone->data);
	write(0, "\n", 2);
	if (zone->size > zone_small)
		return;
	first_bytes = zone_get_first_byte(zone);
	last_bytes = zone_get_last_byte(zone);
	i = 0;
	while (i < divide_ceil(zone->size, ALIGNMENT))
		i = zone_print_chunk(zone, first_bytes, last_bytes, i);
	write(0, "\n", 2);
}
