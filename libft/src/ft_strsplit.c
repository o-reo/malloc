/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 09:43:57 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 15:19:36 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		nb;

	if (!s)
		return (0);
	nb = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] && s[i] == c)
				i++;
			nb++;
		}
		i++;
	}
	if (!s[i] && s[i - 1] != c)
		nb++;
	return (nb);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	char	*dup;
	int		st;
	int		nsub;

	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (count_words(s, c) + 1)))
	|| !s || !(dup = ft_strdup(s)))
		return (NULL);
	i = 0;
	st = 0;
	nsub = 0;
	while (dup[i])
	{
		st = i;
		while (dup[i] && dup[i] != c)
			i++;
		if (st < i)
			if (!(tab[nsub++] = ft_strsub(dup, st, i - st)))
				return (NULL);
		i++;
	}
	ft_strdel(&dup);
	tab[count_words(s, c)] = NULL;
	return (tab);
}
