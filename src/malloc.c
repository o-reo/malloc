/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/12 10:57:45 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/20 17:14:16 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"


void	*malloc(size_t size)
{
	int		page_len;
	void	*ptr;

	page_len = getpagesize();
	if (size <= chunk_tiny_max)
	{
		ptr = memory_map(NULL, size);
	}
	else if (size <= chunk_small_max)
	{
		ptr = memory_map(NULL, size);
	}
	else
	{
		ptr = memory_map(NULL, size);
	}
	return (ptr);
}
