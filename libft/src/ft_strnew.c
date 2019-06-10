/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 09:45:46 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 15:36:10 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char			*str;

	if (!(str = (char *)ft_memalloc(sizeof(char) * (size + 2))))
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
