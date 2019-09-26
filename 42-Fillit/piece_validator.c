#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "fillit.h"

/*static int		g_tet_tab[19][8] = \
{
	//{0,0,0,1,0,2,0,3},	//1
	//{0,0,1,0,2,0,3,0},	//2

	{0,0,1,0,2,0,3,0},	//1
	{0,0,0,1,0,2,0,3},	//2

	{0,0,1,0,0,1,1,1},	//1

	{0,0,0,1,0,2,1,2},	//1
	{0,0,1,0,2,0,0,1},	//2
	{0,0,1,0,1,1,1,2},	//3
	{2,0,0,1,1,1,2,1},	//4

	{1,0,1,1,0,2,1,2},	//1
	{0,0,0,1,1,1,2,1},	//2
	{0,0,1,0,0,1,0,2},	//3
	{0,0,1,0,2,0,2,1},	//4

	{1,0,0,1,1,1,2,1},	//1
	{0,0,0,1,1,1,0,2},	//2
	{0,0,1,0,2,0,1,1},	//3
	{1,0,0,1,1,1,1,2},	//4

	{1,0,2,0,0,1,1,1},	//1
	{0,0,0,1,1,1,1,2},	//2

	{0,0,1,0,1,1,2,1},	//1
	{1,0,0,1,1,1,0,2}	//2
};*/
int 	ret_free(char *del1, char *del2, char *del3, int i)
{
	if (del1)
		free(del1);
	if (del2)
		free(del2);
	if (del3)
		free(del3);
	return (i);
}

void		reset_board(char **board)
{
	int k;

	k = 0;
	while (++k < 27)
		ft_memset(&board[k][0], '.', 27 * sizeof(char));
}

int		is_odd(int i)
{
	return ((i % 2) ? 1 : 0);
}

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

int		shift2(int i, int diff1, int k, int *validate)
{
	int		diff2;
	
	diff1 = g_tet_tab[i][0] - validate[0];
	diff2 = g_tet_tab[i][1] - validate[1];
	while (i < 19 && ++k < 8)
	{
		if (!is_odd(k))
		{
			if (diff1 != g_tet_tab[i][k] - validate[k])
			{
				k = -1;
				diff1 = g_tet_tab[++i][0] - validate[0];
				diff2 = g_tet_tab[i][1] - validate[1];
			}
		}
		else
		{
			if (diff2 != g_tet_tab[i][k] - validate[k])
			{
				k = -1;
				diff1 = g_tet_tab[++i][0] - validate[0];
				diff2 = g_tet_tab[i][1] - validate[1];
			}
		}
	}
	return (k == 8 ? i : -42);
}

int		shift(int i, int j, int *validate, char *ptr[])
{
	int k;

	while (valid_string(ptr[i]) && i < 4)
		i++;
	if (i < 4)
		return (-42);
	i = 0; k = 0;	//set_zero(((size_t)&i, (size_t)&k, 0, 0);
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

int		valid_read(size_t i, int fd, char **av, int *pieces)
{
	size_t	len;
	char	b[546];
	int 	size;

	bzero(b, 546);
	fd = open(av[1], O_RDONLY);
	if (fd >= 0)
	{
		size = read(fd, b, 546);
		if (size > 545 || size < 0)
			return (0);
		len = ft_strlen(b);
		if ((len + 1) % 21)
			return (0);
		pieces[26] = ((int)len + 1) / 21;
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

/*
**	this function returns 0 if piece is a failure
**	this function goes to the next piece if it's a success
*/
int		solver(int *pieces, char  **board, int index, int i)
{
	return (0);
	return (1);
}
int		ft_fillit(int *pieces, char *board[][])
{
	int	move[2];
	int curr[26][8];
	int currp;
	int size;

	// minimum board size
	size = (pieces[26] % 2 ? : pieces[26] / 2 + 1 : pieces[26] / 2);
}

int		check_piece(int size, int *curr, char **board)
{
	int i; 

	i = 0;
	while (i < 0)
	{
		if (__is_alpha(board[i][i + 1]))
			return (0);
		i += 2;
	}
	return (1);
}

void	move_piece(int n, int *move, int *curr)
{
	// for x coordinates
	arr[0] = move[0] + g_tet_tab[n][0];
	arr[2] = move[0] + g_tet_tab[n][2];
	arr[4] = move[0] + g_tet_tab[n][4];
	arr[6] = move[0] + g_tet_tab[n][6];

	// for y coordinates
	arr[1] = move[1] + g_tet_tab[n][1];
	arr[3] = move[1] + g_tet_tab[n][3];
	arr[5] = move[1] + g_tet_tab[n][5];
	arr[7] = move[1] + g_tet_tab[n][7];
}

/*
**	this function starts with reading
**	then validating
**	then fill-it
*/
 
int		main(int ac, char **av)
{
	int		pieces[27];
	char	board[27][27];
	int k;

	k = -1;
	ft_memset((void*)pieces, -1, sizeof(int) * 26);
	if (ac == 2)
		if (!valid_read(0, 0, av, pieces))
		{
			ft_putstr("Error"); 
			exit (1);
		}
	while (++k < 27)
		ft_memset(&board[k][0], '.', 27 * sizeof(char));
//	for (int w = 0; w < 26; w++)
//		printf("%s\n", board[w]);
//	for (int i = 0; i < 27; i++)
//		printf("i = %d, %d\n", (i + 1) ,pieces[i]);
	return (0);
}