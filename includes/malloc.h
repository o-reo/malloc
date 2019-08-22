/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 18:05:14 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/22 17:31:22 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stddef.h>

# define ALIGNMENT_IN_BYTES 2 

enum				e_chunk_size_max
{
	chunk_tiny_max = 8,
	chunk_small_max = 12,
};

enum				e_bool
{
	false,
	true,
};

enum				e_zone_type
{
	zone_empty = 0,
	zone_tiny = 32,
	zone_small = 64,
	zone_large = 65,
};

/*
** Chunks metadata
*/
typedef struct		s_chunk
{
	void			*location;
	size_t			size;
	struct s_chunk	*next;
}					t_chunk;

/*
** Zones linked list
*/
typedef struct		s_zone
{
	void			*location;
	size_t			size;
	t_chunk			*chunks;
	struct s_zone	*next;
}					t_zone;

/*
** Registry linked list
*/
t_zone				*g_zones;

void				write_ptr(void *ptr);
void				write_bin(void *ptr, size_t size);
t_zone				*zone_new(t_zone *prev_zone, size_t size);
void				zone_print(t_zone *zone);
void				zone_chunk_delete(t_zone *zone, t_chunk *chunk);
t_chunk				*zone_chunk_create(t_zone *zone, size_t size);
t_chunk				*chunk_new(size_t size);
void				chunk_free(t_chunk *chunk);
void				*chunk_next(t_chunk *chunk1, t_chunk *chunk2, void *limit);
void				*memory_map(void *location, size_t size);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

#endif
