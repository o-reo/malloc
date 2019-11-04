/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/12 10:51:47 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 17:02:08 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	// write(1, "FREE\n", 5);
	registry_chunk_forget(ptr);
	// write(1, "EXIT FREE\n", 10);
}
