/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 17:34:32 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 15:29:59 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static char	itox(unsigned long x)
{
	if (x > 15)
		return '\0';
	if (x > 9)
	{
		return ('a' + (x - 10));
	}
	return ('0' + x);
}

void		write_ptr(void *ptr)
{
	int				i;
	char			address[11];
	unsigned long	ptr_val;

	address[0] = '0';
	address[1] = 'x';
	
	ptr_val = (unsigned long)ptr;
	i = 0;
	while (i <= 8)
	{
		address[10 - i] = itox(ptr_val & 0x00000000F);
		ptr_val >>= 4;
		i++;
	}
	write(1, address, 11);
}

void		write_bin(void *data, size_t size)
{
	size_t			i;
	char			address[size + 2];
	unsigned long	bin_val;

	address[0] = '0';
	address[1] = 'b';
	
	bin_val = (unsigned long)data;
	i = 0;
	while (i < size)
	{
		address[size - i + 2] = bin_val & 0x000000001 ? '1' : '0';
		bin_val >>= 1;
		i++;
	}
	write(1, address, size + 2);
}

void		write_num(unsigned long	number)
{
	char	num[30];
	int		i;

	i = 0;
	if (number == 0) {
		num[28] = '0';
		i = 1;
	}
	while (number > 0)
	{
		num[28 - i] = '0' + number % 10;
		number /= 10;
		i++;
	}
	num[29] = '\0';
	write(1, num + 28 - i + 1, i + 1);
}

size_t		zone_fill_next_chunk(t_zone *zone, size_t i)
{
	uint32_t	*fbyte;
	uint32_t	*lbyte;

	fbyte = zone_get_first_byte(zone);
	lbyte = zone_get_last_byte(zone);
	i++;
	while (i < zone_bytes_size(zone->size))
	{
		if (((fbyte[i / 32] >> (i % 32)) & 1L) != 0)
			break;
		i++;
	}
	while (i < zone_bytes_size(zone->size))
	{
		ft_bzero(zone->data + zone_quantum(zone->size) * i, zone_quantum(zone->size));
		if (((lbyte[i / 32] >> (i % 32)) & 1L) != 0)
			break;
		i++;
	}
	return (i);
}

void		debug_fill_all()
{
	void	*reg;
	t_zone		*zone;
	size_t		i;

	reg = g_registries;
	while (reg != NULL)
	{
		zone = (t_zone*)(reg + memory_align_size(sizeof(t_registry)));
		while (zone != NULL)
		{
			i = 0;
			while ((i = zone_fill_next_chunk(zone, i)) < zone_bytes_size(zone->size));
			zone = zone->next;
		}
		reg = ((t_registry*)reg)->next;
	}
}
/*

	first_bytes = zone_get_first_byte(zone);
	last_bytes = zone_get_last_byte(zone);
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
*/