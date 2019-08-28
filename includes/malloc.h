/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 18:05:14 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/28 18:38:00 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stddef.h>

# define ALIGNMENT_IN_BYTES 16 
# define PAGE_PER_REGISTRY 4 
# define ZONE_PER_REGISTRY 4  
# define REGISTRY_SIZE 8192  
typedef __int16_t int16_t;
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

/*
** zone size is systematically rounded to the next getpagesize multiple
*/
enum				e_zone_type
{
	zone_empty = 0,
	zone_tiny = 32,
	zone_small = 64,
	zone_large = 65,
};

typedef struct		s_registry
{
	void			*next;
}					t_registry;

/*
** Zones linked list
** after a zone metadata there are two
** rounded zone_size / (8 * ALIGNMENT_IN_BYTES) array containing
** first_bytes and last_bytes
*/
typedef struct		s_zone
{
	void			*data;	
	size_t			size;
}					t_zone;

/*
** Registry linked list
*/
t_registry			*g_registries;

void				write_ptr(void *ptr);
void				write_bin(void *ptr, size_t size);
t_zone				*zone_new(void *header_location, size_t size);
void				zone_print(t_zone *zone);
void				*memory_map(void *location, size_t size);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

#endif
