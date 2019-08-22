/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 15:59:45 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/22 17:49:09 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Maps memory at the given location, size is rounded to match alignment
*/
void	*memory_map(void *location, size_t size)
{
	void	*ptr;

	ptr = mmap(location, size, 
			PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == (void*)-1) {
		return (NULL);
	}
	return (ptr);
}


