#ifndef _MALLOC_H
# define _MALLOC_H

#include <unistd.h>
#include <sys/mman.h>

enum		block_size_max
{
	block_tiny_max = 8,
	block_small_max = 12,
};

enum		zone_size
{
	zone_tiny = 8,
	zone_small = 16,
};

typedef struct	s_zone
{
	void 		*location;
	int 		map;
	enum zone_size 	size;
	struct s_zone 	*next;
}		zone;

void    	free(void *ptr);
void    	*malloc(size_t size);
void    	*realloc(void *ptr, size_t size);

#endif
