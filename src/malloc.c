/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/12 10:57:45 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 16:53:05 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"


void	*malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	registry_init();
	if (size <= chunk_small_max)
	{
		ptr = registry_zone_create_chunk(size);
	}
	else
	{
		write(0, "LARGE ZONE NOT IMPLEMENTED\n", 26);
		ptr = NULL;
	}
	return (ptr);
}
