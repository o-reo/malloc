/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/12 10:57:45 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 17:03:53 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void *malloc(size_t size)
{
	void *ptr;

	// write(1, "MALLOC:", 8);
	ptr = NULL;
	registry_init();
	if (size <= chunk_small_max)
	{
		ptr = registry_zone_create_chunk(size);
	}
	else
	{
		// write(1, "LARGE\n", 7);
		ptr = registry_zone_large(size);
	}
	// ft_bzero(ptr, size);
	// write(1, "EXIT MALLOC\n", 13);
	return (ptr);
}
