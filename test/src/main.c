/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/19 18:21:39 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/28 18:34:44 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

static int	test_zone(void)
{
	
	t_zone	*zone;
	
	write(0, "~----------------------------~\n", 31);
	write(0, "~-------Malloc Testing-------~\n", 31);
	zone = zone_new(NULL, zone_tiny);
	
	zone_print(zone);
	
	return (0);
}

int		main()
{
	test_zone();
    return (0);
}
