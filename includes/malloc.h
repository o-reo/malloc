/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 18:05:14 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 11:10:43 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>

# define QUANTUM_TINY 64
# define QUANTUM_SMALL 512 
# define ALIGNMENT 16
# define REGISTRY_SIZE 4096 

typedef __uint32_t uint32_t;

enum				e_chunk_size_max
{
	chunk_tiny_max = 1024,
	chunk_small_max = 8192,
};

enum				e_bool
{
	e_false,
	e_true,
};

/*
** zone size is systematically rounded to the next getpagesize multiple
** zone size must be a multiple of quantum * 8
*/
enum				e_zone_type
{
	zone_empty = 0,
	zone_tiny = 61440,
	zone_small = 512000,
	zone_large = 512001,
};

typedef struct		s_registry
{
	void			*next;
}					t_registry;

/*
** Zones linked list
** after a zone metadata there are two
** rounded zone_size / (8 * ALIGNMENT) array containing
** first_bytes and last_bytes
*/
typedef struct		s_zone
{
	void			*next;
	void			*data;	
	size_t			size;
}					t_zone;

/*
** Registry linked list
*/
void				*g_registries;

/*
** Main functions
*/
void				show_alloc_mem(void);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

/*
** UTILS
*/
size_t				divide_ceil(size_t num, size_t denom);
void				ft_bzero(void *location, size_t size);

/*
** PRINTING 
*/
void				write_ptr(void *ptr);
void				write_num(unsigned long num);
void				write_bin(void *ptr, size_t size);

/*
** REGISTRY 
*/
void				registry_reset(void);
void				registry_init(void);
void				*registry_append(void);
t_zone				*registry_zone_add(size_t size);
void				*registry_zone_create_chunk(size_t size);
t_zone				*registry_zone_find(void *address);
void				*registry_zone_large(size_t size);
void				registry_chunk_forget(void *address);
void				registry_free_if_empty(void);

/*
** MEMORY MANAGEMENT 
*/
void				*memory_map(void *location, size_t size);
void				memory_unmap(void *location, size_t size);
size_t				memory_align_size(size_t size);

/*
** ZONE
*/
t_zone				*zone_new(void *header_location, size_t size);
void				zone_print(t_zone *zone);
void				*zone_get_first_byte(t_zone *zone);
void				*zone_get_last_byte(t_zone *zone);
void				*zone_chunk_create(t_zone *zone, size_t size);
void				*zone_chunk_register(t_zone *zone, size_t first, 
						size_t last);
enum e_bool			zone_realloc(t_zone *zone, void *address, size_t size);
void				zone_chunk_copy(t_zone *zone, void *src, void *ptr);
enum e_bool			zone_chunk_forget(t_zone *zone, void *address);
enum e_bool			zone_is_empty(t_zone *zone);
void				zone_free(t_zone *zone);
size_t				zone_head_size(size_t size);
size_t				zone_bytes_size(size_t size);
size_t				zone_quantum(size_t size);

#endif
