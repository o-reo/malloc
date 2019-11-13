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
	// ptr = mmap(NULL, size,
	// 		PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

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
	// write_num(size);
	//	write(1, "\n", 1);
	//	write_ptr(ptr);
	//	write(1, "\n", 1);
	// int i = 0;
	// while (i < (int)size){
	// 	((char*)ptr)[i] = 42;
	// 	i++;
	// }
	// write(1, "EXIT MALLOC\n", 13);
	// show_alloc_mem();
	// write_ptr(ptr);
	// write(0, "\n", 2);
	return (ptr);
}
