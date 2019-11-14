/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 18:02:23 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 17:40:18 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	t_zone *zone;
	void *new_ptr;

	// write(1, "REALLOC:", 9);
	if (ptr == NULL)
	{
		// write(1, "EXIT REALLOC (NULL)\n", 21);
		return (malloc(size));
	}
	// return (ptr);
	// return (NULL);
	// new_ptr = malloc(size);
	if (!(zone = registry_zone_find(ptr)))
	{
		// write(1, "EXIT REALLOC (KO)\n", 19);
		// new_ptr = malloc(size);
		return (ptr);
	}
	if (zone_realloc(zone, ptr, size) == e_true)
	{
		// write_num(size);
		// ft_bzero(ptr, size);
		// write(1, "EXIT REALLOC (OK)\n", 19);
		return (ptr);
	}
	// show_alloc_mem();
	// write_num(size);
	// write_ptr(zone->data);
	// write_ptr(ptr);
	new_ptr = malloc(size);
	zone_chunk_copy(zone, ptr, new_ptr);
	free(ptr);
	// write(1, "EXIT REALLOC\n", 14);
	return (new_ptr);
}
