/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   memory.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/27 16:15:42 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 15:09:16 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** round a specified size to the next page_size multiple
*/
size_t	memory_size_to_page(size_t size)
{
	int		page_size;

	page_size = getpagesize();
	return (page_size * divide_ceil(size, page_size));
}

/*
** Maps size bytes of memory near the given location, size is rounded up to be
** a multiple of getpagesize
** @return the true location of the mapped memory
*/
void	*memory_map(void *location, size_t size)
{
	void	*ptr;

	location = NULL;
	ptr = mmap(NULL, memory_size_to_page(size), 
			PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == (void*)-1) {
		return (NULL);
	}
	return (ptr);
}

size_t	memory_align_size(size_t size)
{
	return (size + size % ALIGNMENT);
}

void	memory_unmap(void *location, size_t size)
{
	munmap(location, memory_size_to_page(size));
}
