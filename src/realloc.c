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

void	*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	void	*new_ptr;

//	write(1, "REALLOC\n", 8);
	if (!(zone = registry_zone_find(ptr)))
			return (NULL);
	//if (zone_realloc(zone, ptr, size) == e_true)
	//	return (ptr);
	//else {
	new_ptr = malloc(size);
	//	zone_chunk_copy(zone, ptr, new_ptr);
	//	free(ptr);
	//}
//	write(1, "EXIT REALLOC\n", 14);
	return (new_ptr);
}
