/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_next_line.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: eruaud <eruaud@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/02 15:25:57 by eruaud       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 16:07:42 by eruaud      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static t_list	*find_fd(t_list **lst, int const fd)
{
	t_list		*new;

	new = *lst;
	while (new && fd != (int)(new->content_size))
		new = new->next;
	if (!new)
	{
		new = ft_lstnew(NULL, 0);
		ft_lstadd(lst, new);
		new->content_size = (int)fd;
	}
	return (new);
}

static int		current_line(char **line, t_list **str, int flag)
{
	int		i;

	i = 0;
	while (((char*)((*str)->content))[i] &&
			((char*)((*str)->content))[i] != '\n')
		i++;
	*line = ft_strsub((*str)->content, 0, i);
	(*str)->content = (char*)ft_memmove((*str)->content,
			ft_strchr((*str)->content, '\n') + 1,
			ft_strlen(ft_strchr((*str)->content, '\n')));
	if (!flag)
		(*str)->content = NULL;
	return (1);
}

static char		*strmerge(char *s1, char *s2)
{
	char	*str;

	str = s1;
	s1 = ft_strjoin(s1, s2);
	ft_strdel(&str);
	return (s1);
}

int				get_next_line(int const fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*lst;
	t_list			*cur;
	int				rd;

	if (read(fd, NULL, 0) == -1 || !line)
		return (-1);
	cur = find_fd(&lst, fd);
	if (ft_strlen(cur->content) > 0 && ft_strchr(cur->content, '\n'))
		return (current_line(line, &cur, 1));
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		buf[rd] = '\0';
		cur->content = !cur->content ? ft_strdup(buf)
			: strmerge(cur->content, buf);
		if (ft_strchr(cur->content, '\n'))
			return (current_line(line, &cur, 1));
	}
	if (ft_strlen(cur->content) > 0)
		return (current_line(line, &cur, 0));
	return (0);
}
