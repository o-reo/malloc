/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 18:05:14 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 12:37:34 by eruaud      ###    #+. /#+    ###.fr     */
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

typedef __int64_t int64_t;

enum				e_chunk_size_max
{
	chunk_tiny_max = 32,
	chunk_small_max = 64,
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
	zone_tiny = 4096,
	zone_small = 8192,
	zone_large = 8193,
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
extern void			*g_registries;

enum e_bool			zone_check_range(t_zone *zone, void *address);
void				*zone_chunk_create(t_zone *zone, size_t size);
void				zone_chunk_forget(t_zone *zone, void *address);
void				registry_init(void);
void				registry_append(void);
t_zone				*registry_zone_add(size_t size);
void				write_ptr(void *ptr);
void				write_num(unsigned long num);
void				write_bin(void *ptr, size_t size);
t_zone				*zone_new(void *header_location, size_t size);
void				zone_print(t_zone *zone);
void				*memory_align(void *address);
void				*memory_map(void *location, size_t size);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

#endif
