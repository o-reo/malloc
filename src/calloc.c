/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/02 17:28:40 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 17:31:04 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void *calloc(size_t count, size_t size)
{
	void *ptr;

	// write(1, "CALLOC:", 8);
	ptr = malloc(count * size);
	ft_bzero(ptr, count * size);
	// write(1, "CALLOC EXIT\n", 13);
	return (ptr);
}
