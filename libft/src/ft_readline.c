/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_readline.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/02 15:25:57 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2019/01/11 12:20:53 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		ft_current_line(char **line, char **str, int flag)
{
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	*line = ft_strsub(*str, 0, i);
	*str = (char*)ft_memmove(*str, ft_strchr(*str, '\n') + 1,
			ft_strlen(ft_strchr(*str, '\n')));
	if (!flag)
		ft_strdel(str);
	return (1);
}

static char		*ft_strmerge(char *s1, char *s2)
{
	char	*str;

	str = s1;
	s1 = ft_strjoin(str, s2);
	ft_strdel(&str);
	return (s1);
}

int				ft_readline(int const fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static char		*str;
	int				rd;

	if (read(fd, NULL, 0) == -1 || !line)
		return (-1);
	if (ft_strlen(str) > 0 && ft_strchr(str, '\n'))
		return (ft_current_line(line, &str, 1));
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		buf[rd] = '\0';
		str = !str ? ft_strdup(buf) : ft_strmerge(str, buf);
		if (ft_strchr(str, '\n'))
			return (ft_current_line(line, &str, 1));
	}
	if (ft_strlen(str) > 0)
	{
		return (ft_current_line(line, &str, 0));
	}
	ft_strdel(&str);
	return (0);
}
