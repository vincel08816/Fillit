/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:52:06 by vilee             #+#    #+#             */
/*   Updated: 2019/09/14 10:22:00 by vilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	This function should return 3 things
**		1.)	if '\n', return 1;
**		2.) if EOF, return 0;
**		3.) if error, return -1;
*/

/*static size_t	strichr(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}*/

static void		ft_combine2(char **tmp, char *buff)
{
	char *del;

	del = *tmp;
	*tmp = ft_strjoin(*tmp, buff);
	free(del);
}

/*
**	reject_line strdup's up to /n by using
**	strichr to find the index of \n
**	using the pointer after the \n and copying the rest to
**	the static variable s[fd] from the main GNL
*/

static int		reject_line(int size, char **line, char **tmp, char **s)
{
	size_t	i;
	char	*start;

	if (!size)
	{
		free(*tmp);
		return (0);
	}
	i = 0;
	start = *tmp;
	i = strichr(*tmp, '\n');
	*line = ft_strsub(*tmp, 0, i);
	*tmp += i + 1;
	*s ? free(*s) : 0;
	if (**tmp != '\0' || **tmp != '\n')
		*s = ft_strdup(*tmp);
	ft_strdel(&start);
	return (1);
}

/*
**	function uses read() to return 0, 1, -1 for EOF, \n, err
**	read() loop breaks when \n or \0 is found
**	strichr i will find \n and size == 0 will signify the end of file
**	the static character will read
*/

int				get_next_line(int fd, char **line)
{
	static char *s[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			size;

	size = 1;
	if (fd < 0 || fd > MAX_FD || !line || (read(fd, 0, 0) < 0))
		return (-1);
	tmp = ft_strdup("");
	s[fd] ? ft_combine2(&tmp, s[fd]) : 0;
	if (strichr(tmp, '\n') < ft_strlen(tmp))
		return (reject_line(size, line, &tmp, &s[fd]));
	while ((size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[size] = '\0';
		ft_combine2(&tmp, buff);
		if (strichr(buff, '\n') < ft_strlen(buff))
			break ;
	}
	if (!s[fd])
		return (reject_line(1, line, &tmp, &s[fd]));
	(ft_strcmp(tmp, "")) ? size++ : 0;
	return (reject_line(size, line, &tmp, &s[fd]));
}

/*
**	#include <stdio.h>
**	
**	int main(int argc, char **argv)
**	{
**		char *line;
**		int fd;
**	
**		fd = open(argv[1], O_RDONLY);
**		if (argc != fd)
**			line = NULL;
**		while (get_next_line(fd, &line) > 0)
**		{
**			printf("%s\n", line);
**			free(line);
**		}
**		return (0);
**	}
*/
