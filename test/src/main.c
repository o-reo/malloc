/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 14:13:52 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 11:42:55 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"
#include <assert.h>
#include <stdio.h>

static int	test_zone(void)
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

static int	test_registry(void)
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

static int	test_malloc(void)
{
	int		i;
	void	*ptr;

	registry_reset();
	i = 1000;
	ptr = NULL;
	while (i--)
	{
		ptr = malloc(1024);
		((char*)ptr)[1023] = 42;
	}
	malloc(1025);
	show_alloc_mem();
	return (0);
}

static int	test_free(void)
{
	
	int		i;
	void	*ptr;

	registry_reset();
	i = 10;
	ptr = NULL;
	while (i--)
	{
		ptr = malloc(1024);
		((char*)ptr)[0] = 42;
		free(ptr);
	}
	
	show_alloc_mem();
	
	return (0);

	}

int		main()
{
	write(1, "~----------------------------~\n", 31);
	write(1, "~-------Malloc Testing-------~\n", 31);
	test_zone();
	test_registry();
	test_malloc();
	test_free();
	return (0);
}
