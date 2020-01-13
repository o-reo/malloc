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

	ptr = NULL;
	registry_init();
	if (size <= chunk_small_max)
	{
		ptr = registry_zone_create_chunk(size);
	}
	else
	{
		ptr = registry_zone_large(size);
	}
	return (ptr);
}
