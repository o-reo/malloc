/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/06 17:31:45 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 17:36:57 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Returns the first byte word at the specified index
*/

void			*zone_get_last_byte(t_zone *zone)
{
	return (zone + sizeof(t_zone) + zone->size / ALIGNMENT_IN_BYTES);
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
	while (i < zone->size / ALIGNMENT_IN_BYTES)
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
	while (i < zone->size / ALIGNMENT_IN_BYTES)
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

	first_byte = 0;
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
	return (i);
}

void			zone_print(t_zone *zone)
{
	size_t	i;
	int64_t *first_bytes;
	int64_t *last_bytes;

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
	while (i < zone->size / ALIGNMENT_IN_BYTES)
		i = zone_print_chunk(zone, first_bytes, last_bytes, i) + 1;
	write(0, "\n", 2);
}
