#include "malloc.h"

int main()
{
	ft_bzero(malloc(1024), 1024);
	ft_bzero(malloc(1024 * 32), 1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
