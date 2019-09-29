#include "fillit.h"

/*
**	checks if string is length of 4
**	checks if it is '#' and '.'
**	returns 1 on success and 0 on failure
*/
int		valid_string(char *s)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	while (s[i] == '#' || s[i] == '.')
		i++;
	return ((len == 4 && i == len) ? 1 : 0);
}

/*
**
*/

int		shift(size_t i, size_t j, int *validate, char *ptr[])
{
	size_t k;

	while (valid_string(ptr[i]) && i < 4)
		i++;
	if (i < 4)
		return (-42);
	set_zero(&i, &k, 0, 0);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (ptr[i][j] == '#')  
			{
				if (k == 8)
					return (-42);
				validate[k++] = j;
				validate[k++] = i;
			}
			j++;
		}
		i++;
	}
	return (shift2(0, 0, -1, validate));
}

int		shift2(int i, int diff1, int k, int *validate)
{
	int		diff2;
	
	diff1 = g_tet[i][0] - validate[0];
	diff2 = g_tet[i][1] - validate[1];
	while (i < 19 && ++k < 8)
	{
		if (!(k % 2))	//(!is_odd(k))
		{
			if (diff1 != g_tet[i][k] - validate[k])
			{
				k = -1;
				diff1 = g_tet[++i][0] - validate[0];
				diff2 = g_tet[i][1] - validate[1];
			}
		}
		else
		{
			if (diff2 != g_tet[i][k] - validate[k])
			{
				k = -1;
				diff1 = g_tet[++i][0] - validate[0];
				diff2 = g_tet[i][1] - validate[1];
			}
		}
	}
	return (k == 8 ? i : -42);
}

int		valid_read(size_t i, int fd, char **av, int *pieces)
{
	size_t	len;
	char	b[545];
	int 	size;

	bzero(b, 545);
	fd = open(av[1], O_RDONLY);
	if (fd >= 0)
	{
		size = read(fd, b, 545);
		if (size > 544 || size < 0)
			return (0);
		len = ft_strlen(b);
		if ((len + 2) % 21)
			return (0);
		pieces[26] = ((int)len + 2) / 21;
		while (i < len)
			b[i] == '\n' ? b[i++] = '\0': i++;
		return (valid_read2(pieces, b, len, 0));
	}
	return (0);
}

int 	valid_read2(int *p, char *ptr, size_t len, size_t i)
{
	char	*tmp[5];
	int 	validate[8];
	int 	j;

	j = 0;
	while (i < len)
	{
		tmp[0] = ptr + i;
		tmp[1] = ptr + i + 5;
		tmp[2] = ptr + i + 10;
	 	tmp[3] = ptr + i + 15;
		tmp[4] = ptr + i + 20;
		if ((p[j++] = shift(0,  0, validate, tmp)) < 0)
			return (0);
		i += 21;
	}
	return (1);
}
