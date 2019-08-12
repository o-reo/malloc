#include "malloc.h"

void	*map_block(void *location, int blocksize)
{
	void *ptr;

    	ptr = mmap(NULL, blocksize, PROT_READ | PROT_WRITE,
               MAP_ANON | MAP_PRIVATE, -1, 0);

    return (ptr);
}

void	*malloc(size_t size) {
  int	pagelen;
  void	*ptr;

  pagelen = getpagesize();

  if (size <= block_tiny_max)
  {
	  ptr = map_block(size)
  }
  else if (size <= block_small_max)
  {
	  ptr = map_block(size);
  }
  else
  {
	  ptr = map_block(size);
  }
  return ptr;
}
