/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chunk.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 14:40:04 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/22 17:47:12 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Init a chunk with default values
*/
t_chunk			*chunk_new(size_t size)
{
	t_chunk		*chunk;

	chunk = memory_map(NULL, sizeof(chunk));
	chunk->size = size;
	chunk->location = NULL;
	chunk->next = NULL;
	return (chunk);
}

void			chunk_free(t_chunk *chunk)
{
	munmap(chunk, sizeof(t_chunk));
}


/*
** Computes the space between the next alignment and the next chunk
*/
void			*chunk_next(t_chunk *chunk1, t_chunk *chunk2, void *limit)
{
	void	*align_ptr;
		
	align_ptr = chunk1->location + chunk1->size;
	while (((unsigned long)align_ptr & ALIGNMENT_IN_BYTES) != 0)
	{
		align_ptr++;
	}
	if (!chunk2) {
		return (align_ptr + chunk1->size < limit ? 
				align_ptr : NULL);
	}
	return (align_ptr + chunk1->size < chunk2->location ? align_ptr : NULL);
}
