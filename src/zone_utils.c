/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/06 17:31:45 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 18:08:00 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Returns the first byte word
*/

void			*zone_get_first_byte(t_zone *zone)
{
	return ((void*)zone + memory_align_size(sizeof(t_zone)));
}

/*
** Returns the last byte word
*/

void			*zone_get_last_byte(t_zone *zone)
{
	return (zone_get_first_byte(zone) + zone_bytes_size(zone->size));
}

void			zone_print_mask(t_zone *zone)
{
	size_t		i;
	uint32_t	*first_bytes;
	uint32_t	*last_bytes;

	first_bytes = (uint32_t*)zone_get_first_byte(zone);
	i = 0;
	while (i < 8 * zone_bytes_size(zone->size))
	{
		if ((first_bytes[i / 32] >> i % 32) & 1)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i++;
	}
	write(0, "\n", 1);
	last_bytes = (uint32_t*)zone_get_last_byte(zone);
	i = 0;
	while (i < 8 * zone_bytes_size(zone->size))	{
		(last_bytes[i / 32] >> i % 32) & 1 ? write(1, "1", 1) :
			write(1, "0", 1);
		i++;
	}
	write(0, "\n", 1);
}

static size_t	zone_print_chunk(t_zone *zone, uint32_t *first_bytes,
		uint32_t *last_bytes, size_t i)
{
	size_t	first_byte;
	size_t	current_size;
	size_t	quantum;

	quantum = zone_quantum(zone->size);
	current_size = 8 * zone_bytes_size(zone->size);
	first_byte = 0;
	while (((first_bytes[i / 32] >> (i % 32)) & 1L) == 0 
			&& i < current_size)
		i++;
	first_byte = i;
	while (((last_bytes[i / 32] >> (i % 32)) & 1L) == 0 
			&& i < current_size)
		i++;
	if (i >= current_size)
		return (current_size);
	write_ptr(zone->data + first_byte * quantum);
	write(1, " - ", 3);
	write_ptr(zone->data + (i + 1) * quantum - 1);
	write(1, ": ", 2);
	write_num((i - first_byte + 1) * quantum);
	write(1, " octets\n", 8);
	return (i + 1);
}

void			zone_print_large(t_zone *zone)
{
	write_ptr(zone->data);
	write(1, " - ", 3);
	write_ptr(zone->data + zone->size - 1);
	write(1, ": ", 2);
	write_num(zone->size);
	write(1, " octets\n", 8);
}

void			zone_print(t_zone *zone)
{
	size_t	i;
	uint32_t *first_bytes;
	uint32_t *last_bytes;

	if (zone->size == zone_empty)
		return;
	if (zone->size <= zone_tiny)
		write(1, "TINY : ", 7);
	else if (zone->size <= zone_small)
		write(1, "SMALL : ", 8);
	else
		write(1, "LARGE : ", 8);
	write_ptr(zone->data);
	write(1, "\n", 2);
	if (zone->size > zone_small)
	{
		zone_print_large(zone);
		return;
	}
	first_bytes = zone_get_first_byte(zone);
	last_bytes = zone_get_last_byte(zone);
	i = 0;
	while (i < 8 * zone_bytes_size(zone->size))
		i = zone_print_chunk(zone, first_bytes, last_bytes, i);
	write(1, "\n", 2);
}
