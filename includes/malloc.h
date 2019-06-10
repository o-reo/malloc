#ifndef _MALLOC_H
# define _MALLOC_H

#include <unistd.h>
#include <sys/mman.h>

#define TINY_BLOCKSIZE 8
#define SMALL_SIZE 8
#define SMALL_BLOCKSIZE 16
#define LARGE_SIZE

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);

#endif
