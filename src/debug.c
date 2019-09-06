/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 17:34:32 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/30 16:13:41 by eruaud      ###    #+. /#+    ###.fr     */
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
	write(0, num + 28 - i + 1, i + 1);
}
