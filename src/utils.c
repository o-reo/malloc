/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/11 16:37:13 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 14:44:58 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

size_t		divide_ceil(size_t num, size_t denom)
{
	return (num / denom + ((num % denom) != 0));
}

void		ft_bzero(void *location, size_t size)
{
	size_t		i;

	i = size - 1;
	while (size--)
		((char*)location)[size] = 0;
}
