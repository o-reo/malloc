/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:21:39 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 17:46:06 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"
#include <assert.h>
#include <stdio.h>

static int	test_zone(void)
{
	t_zone		*zone;
	void		*chunk;
	void		*chunk1;

	write(0, "~----------------------------~\n", 31);
	write(0, "~-------Malloc Testing-------~\n", 31);

	write(0, "--     Initialiazing registry \n", 31);
	registry_init();
	
	write(0, "--     Zone creation          \n", 31);
	zone = registry_zone_add(zone_tiny);	
	assert(zone != NULL);	
	
	write(0, "--     Chunk creation         \n", 31);
	write(0, "--- Too large                 \n", 31);
	chunk = zone_chunk_create(zone, 900000);
	assert(chunk == NULL);
	write(0, "--- Size zero                 \n", 31);
	chunk = zone_chunk_create(zone, 0);
	assert(chunk != NULL);
	write(0, "--- One byte                  \n", 31);
	chunk = zone_chunk_create(zone, 1);
	((char*)chunk)[0] = 'a';
	assert(chunk != NULL && ((char*)chunk)[0] == 'a');
	
	write(0, "--- Four bytes                \n", 31);
	((long double*)chunk)[0] = 1;
	((long double*)chunk)[1] = 2;
	((long double*)chunk)[2] = 3;
	((long double*)chunk)[3] = 4;
	assert(chunk != NULL && ((long double*)chunk)[2] == 3);
	chunk1 = zone_chunk_create(zone,  16);
	assert(chunk != NULL);
	
	write(0, "--     Chunk forget           \n", 31);
	zone_chunk_forget(zone, chunk1);
	zone_chunk_forget(zone, chunk);

	return (0);
}

int		main()
{
	test_zone();
    return (0);
}
