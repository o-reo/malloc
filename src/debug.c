/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 17:34:32 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 17:34:58 by eruaud      ###    #+. /#+    ###.fr     */
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
	write(0, address, 11);
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
	write(0, address, size + 2);
}
