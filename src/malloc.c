#include "malloc.h"

void *malloc(size_t size) {
  void *ptr;

  ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  (void)size;
  return ptr;
}
