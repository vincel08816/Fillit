#include "fillit.h"

int			invalid_string(char const *s, int *count)
{
	while (*s && (*s != '.' || *s != '#'))
	{
		if (*s == '#')
			*count++;
		s++;
	}
	return (!(&s[ft_strlen(s)] - s) ? 0 : 1);
}

char		*something(char **av, idk **any)
{
	int		i = 0;
	int		fd;
	int		c;
	char	*ret[5];
	char	*l = NULL;

	fd = open(av[1], O_RDONLY);
	if (fd >= 0)
	{
		while (get_next_line(fd, &l) > 0)
		{
			if (ft_strlen(l) > 5 || c > 5 || \
				invalid_string(l, &c))
				break;
				//error line
			if (i >= 4)
				break;
			ret[i++] = l;
		}
		close(fd);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	char	*bigsomething;
	idk		*anything;

	anything = (idk *)malloc(sizeof(idk));
	something(av, &anything);
	printf ("%s", bigsomething);
	return (0);
}
