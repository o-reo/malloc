/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 14:13:52 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 17:23:13 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"
#include <assert.h>
#include <stdio.h>

int	test_zone(void)
{
	/*
	t_zone		*zone;
	void		*chunk;
	void		*chunk1;
	void		*chunk2;

	write(1, "- Testing Zones               \n", 31);
	write(1, "--     Initializing registry  \n", 31);
	registry_reset();
	registry_init();
	
	write(1, "--     Zone creation          \n", 31);
	zone = registry_zone_add(zone_small);	
	assert(zone != NULL);	
	
	write(1, "--     Chunk creation         \n", 31);
	write(1, "---       Too large           \n", 31);
	chunk = zone_chunk_create(zone, 900000);
	assert(chunk == NULL);
	write(1, "---       Size zero           \n", 31);
	chunk = zone_chunk_create(zone, 0);
	assert(chunk != NULL);
	write(1, "---       One byte            \n", 31);
	chunk = zone_chunk_create(zone, 1);
	
	((char*)chunk)[0] = 'a';
	assert(chunk != NULL && ((char*)chunk)[0] == 'a');
	
	write(1, "---       Four bytes         \n", 31);
	((long double*)chunk)[0] = 1;
	((long double*)chunk)[1] = 2;
	((long double*)chunk)[2] = 3;
	((long double*)chunk)[3] = 4;
	assert(chunk != NULL && ((long double*)chunk)[2] == 3);
	chunk1 = zone_chunk_create(zone,  16);
	assert(chunk != NULL);
	
	write(1, "---       Many bytes         \n", 31);
	chunk2 = zone_chunk_create(zone,  1024);
	
	write(1, "--        Chunk forget       \n", 31);
	assert(zone_chunk_forget(zone, chunk1) == e_true);
	assert(zone_chunk_forget(zone, chunk1) == e_false);
	assert(zone_chunk_forget(zone, chunk) == e_true);
	assert(zone_chunk_forget(zone, chunk) == e_false);
	assert(zone_chunk_forget(zone, chunk2) == e_true);
	assert(zone_chunk_forget(zone, chunk2) == e_false);
	*/
	return (0);
}

int	test_registry(void)
{
	/*
	t_zone	*zone;
	t_zone	*zone2;
	void	*chunk;

	write(1, "- Testing Registries         \n", 31);
	registry_reset();
	registry_init();
	zone = registry_zone_add(zone_tiny);
	zone2 = registry_zone_find(zone->data + 1);
	assert(zone == zone2);
	chunk = registry_zone_create_chunk(612);
	zone_print(zone);
	*/
	return (0);
}
# include <string.h>
int	test_error(void)
{
	void	*ptr[5000];
	// Test 0
	ptr[0] = malloc(0);
	if ((uint32_t)ptr[0] % 16 != 0)
		return (-1);
	free(ptr[0]);
	// Test 1 
	int i = 1;
	while (i < 5000)
	{
		ptr[i] = malloc(i);
		memset(ptr[i], 'a', i);	
		i += 3;
	}
	// Test 2
	i = 1;
	while (i < 5000)
	{
		char cmp[i];
	 	memset(cmp, 'a', i);
		if (memcmp(cmp, ptr[i], i) != 0)
			return (-1);
		i += 3;
	}
	
	// Free not allocated
	free((void*)92);
	
	// Realloc
	void *re = malloc(50);
	realloc(re, 50000);	
	return (0);
}

int	test_malloc(void)
{
	int		i;
	void	*ptr;

	//registry_reset();
	i = 500;
	ptr = NULL;
	while (i--)
	{
		ptr = malloc(512000);
		((char*)ptr)[511999] = 42;
		free(ptr);
	}
	while (i++ < 2000)
	{
		ptr = malloc(10000);
		free(ptr);
	}
	show_alloc_mem();
	return (0);
}

int	test_free(void)
{
	
	int		i;
	void	*ptr;

	registry_reset();
	i = 10;
	ptr = NULL;
	while (i--)
	{
		//ptr = malloc(1024);
		//((char*)ptr)[0] = 42;
		//free(ptr);
	}
	
	//show_alloc_mem();
	
	return (0);

	}

int		main()
{
	write(1, "~----------------------------~\n", 31);
	write(1, "~-------Malloc Testing-------~\n", 31);
	test_error() != 0 ? write(1, "KO\n", 3) : write(1, "OK\n", 3);
	//test_zone();
	//test_registry();
	//test_malloc();
	//test_free();
	return (0);
}
