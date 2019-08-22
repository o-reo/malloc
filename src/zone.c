/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zone.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:04:51 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/22 17:30:35 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

/*
** Init a zone
*/
t_zone	*zone_new(t_zone *prev_zone, size_t size)
{
	t_zone	*new_zone;
   
	new_zone = memory_map(prev_zone, sizeof(t_zone));
	if (prev_zone) {
		new_zone->location = memory_map(prev_zone->location, size);
		prev_zone->next = new_zone;
	}
	else
	{
		new_zone->location = memory_map(NULL, size);
	}
	new_zone->size = size;
	new_zone->chunks = NULL;
	new_zone->next = NULL;
	return (new_zone);
}

void	zone_print(t_zone *zone)
{
	t_chunk		*i_chunk;

	if (zone->size <= zone_tiny)
	{
		write(0, "TINY : ", 7);
	}
	else if (zone->size <= zone_small)
	{
		write(0, "SMALL : ", 8);
	}
	else
	{
		write(0, "LARGE : ", 8);
	}
	write_ptr(zone->location);
	write(0, "\n", 2);
	i_chunk = zone->chunks;
	while (i_chunk)
	{
		write_ptr(i_chunk->location);
		write(0, " - ", 4);
		write_ptr(i_chunk->location + i_chunk->size - 1);
		write(0, "\n", 2);
		i_chunk = i_chunk->next;
	}
}

/*
** Delete the chunk
*/
void			zone_chunk_delete(t_zone *zone, t_chunk *chunk)
{
	t_chunk		*i_chunk;
	t_chunk		*prev_chunk;

	// get chunk in linked list
	i_chunk = zone->chunks;
	while (i_chunk && i_chunk != chunk)
	{
		prev_chunk = i_chunk;
		i_chunk = i_chunk->next;
	}
	// not found
	if (!i_chunk)
		return;
	if (i_chunk == zone->chunks)
	{
		zone->chunks = i_chunk->next;
	
	}
	else 
	{
		prev_chunk->next = i_chunk->next;
	}
	chunk_free(chunk);
}

/*
** Insert a chunk in the linked list
** @return the new chunk or NULL if zone has no sufficient contiguous space
*/
t_chunk			*zone_chunk_create(t_zone *zone, size_t size)
{
	t_chunk			*chunk;
	t_chunk			*i_chunk;
	t_chunk			*i_chunk_prev;

	chunk = chunk_new(size);
	if (zone->chunks == NULL)
	{
		if (zone->size < size) { return (NULL);}
		chunk->location = zone->location;
		zone->chunks = chunk;
		return (chunk);
	}
	i_chunk = zone->chunks->next;
	i_chunk_prev = zone->chunks;
	while (i_chunk_prev)
	{
		if (!(chunk->location = chunk_next(i_chunk_prev, i_chunk, 
						zone->location + zone->size)))
		{
			chunk->location = i_chunk_prev->location + i_chunk_prev->size;	
			chunk->next = i_chunk;
			i_chunk_prev->next = chunk;
			return (chunk);
		}
		i_chunk_prev = i_chunk;
		i_chunk = i_chunk ? i_chunk->next : NULL;
	}
	chunk_free(chunk);
	return (NULL);
}
