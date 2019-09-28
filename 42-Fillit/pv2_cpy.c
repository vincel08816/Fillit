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

void		reset_board(char board[27][27])
{
	int k;
	int j;

	k = -1;
	while (++k < 27)
	{
		j = -1;
		while (++j < 27)
			board[k][j] = '.';
	}
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

void	print_board(int size, char board[27][27])
{
	int k;

	k = -1;
	printf("\n");
	while (++k < size)
	{
		write(1, "\t", 1);
		write(1, board[k], size);
		write(1, "\n", 1);
	}
	printf("\n");
}

int		ft_load(char board[27][27], int i, int m[2], int *p)
{
	printf("ft_load m[0]: %d , m[1] : %d\n", m[0], m[1]);
	board[g_tet_tab[p[i]][1] + m[1]][g_tet_tab[p[i]][0] + m[0]] = i + 'A';
	board[g_tet_tab[p[i]][3] + m[1]][g_tet_tab[p[i]][2] + m[0]] = i + 'A';
	board[g_tet_tab[p[i]][5] + m[1]][g_tet_tab[p[i]][4] + m[0]] = i + 'A';
	board[g_tet_tab[p[i]][7] + m[1]][g_tet_tab[p[i]][6] + m[0]] = i + 'A';
	print_board(p[27], board);
}

int		ft_shit(char board[27][27], int i, int *m, int *p)
{
	board[g_tet_tab[p[i]][1] + m[1]][g_tet_tab[p[i]][0] + m[0]] = '.';
	board[g_tet_tab[p[i]][3] + m[1]][g_tet_tab[p[i]][2] + m[0]] = '.';
	board[g_tet_tab[p[i]][5] + m[1]][g_tet_tab[p[i]][4] + m[0]] = '.';
	board[g_tet_tab[p[i]][7] + m[1]][g_tet_tab[p[i]][6] + m[0]] = '.';
}

int		check_piece(int i, int *p, int m[2], char board[27][27])
{
	int n;
	
	n = 0;
	if (!(g_tet_tab[i][8] + m[0] < p[27]) || !(g_tet_tab[i][9] + m[1] < p[27]))
		return (-1);
	while (n < 8)
	{
		if (ft_isalpha(board[g_tet_tab[p[i]][n + 1] + \
		m[1]][g_tet_tab[p[i]][n] + m[0]]))
		{
			return (0);
		}
		n += 2;
	}
	return (1);
}

int		check_empty(int *p, int i, int m[2], char board[27][27])
{

	int val;

	while (1)
	{
		if (!(g_tet_tab[i][8] + m[0] < p[27]) || !(g_tet_tab[i][9] + m[1] < p[27]))
			return (0);
		while ((val = !check_piece(i, p, m#include <stdlib.h>
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

void		reset_board(char board[27][27])
{
	int k;
	int j;

	k = -1;
	while (++k < 27)
	{
		j = -1;
		while (++j < 27)
			board[k][j] = '.';
	}
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

void	print_board(int size, char board[27][27])
{
	int k;

	k = -1;
	printf("\n");
	while (++k < size)
	{
		write(1, "\t", 1);
		write(1, board[k], size);
		write(1, "\n", 1);
	}
	printf("\n");
}

int		ft_load(char board[27][27], int i, int m[2], int *p)
{
	printf("ft_load m[0]: %d , m[1] : %d\n", m[0], m[1]);
	board[g_tet_tab[p[i]][1] + m[1]][g_tet_tab[p[i]][0] + m[0]] = i + 'A';
	board[g_tet_tab[p[i]][3] + m[1]][g_tet_tab[p[i]][2] + m[0]] = i + 'A';
	board[g_tet_tab[p[i]][5] + m[1]][g_tet_tab[p[i]][4] + m[0]] = i + 'A';
	board[g_tet_tab[p[i]][7] + m[1]][g_tet_tab[p[i]][6] + m[0]] = i + 'A';
	print_board(p[27], board);
}

int		ft_shit(char board[27][27], int i, int *m, int *p)
{
	board[g_tet_tab[p[i]][1] + m[1]][g_tet_tab[p[i]][0] + m[0]] = '.';
	board[g_tet_tab[p[i]][3] + m[1]][g_tet_tab[p[i]][2] + m[0]] = '.';
	board[g_tet_tab[p[i]][5] + m[1]][g_tet_tab[p[i]][4] + m[0]] = '.';
	board[g_tet_tab[p[i]][7] + m[1]][g_tet_tab[p[i]][6] + m[0]] = '.';
}

int		check_piece(int i, int *p, int m[2], char board[27][27])
{
	int n;
	
	n = 0;
	if (!(g_tet_tab[i][8] + m[0] < p[27]) || !(g_tet_tab[i][9] + m[1] < p[27]))
		return (-1);
	while (n < 8)
	{
		if (ft_isalpha(board[g_tet_tab[p[i]][n + 1] + \
		m[1]][g_tet_tab[p[i]][n] + m[0]]))
		{
			return (0);
		}
		n += 2;
	}
	return (1);
}

int		check_empty(int *p, int i, int m[2], char board[27][27])
{

	int val;

	while (1)
	{
		if (!(g_tet_tab[i][8] + m[0] < p[27]) || !(g_tet_tab[i][9] + m[1] < p[27]))
			return (0);
		while ((val = !check_piece(i, p, m, board)) == 0)
		{
			(p[27] > g_tet_tab[i][8] + m[0]) ? m[0]++ : 0;
			if (p[27] > g_tet_tab[i][9] + m[1]) 
			{
				m[0] = 0;
				m[1]++;
			}
		}
		if (val == 1)
			return (1);
	}
	return (1);
}

//	return (1) is complete
//	return (0) is not working
//	return (-1) increase board_size;
//	
int 	ft_solver(int i, int *p, char board[27][27])
{
	int var;
	int n;
	int m[2];

	n = 0; m[0] = 0; m[1] = 0;
	while (p[i] != -1)
	{
//		if (var = isvalid + place piece)
		if ((var = check_empty(p, i, m, board)) == 1)
		{
			ft_load(board, i, m, p);
			var = ft_solver(i + 1, p, board);
		}
		if (var == 0)
			ft_shit(board, i, m, p);
		if (var < 0)
			return (var);
	}
	return (2);
}

int 	ft_fill(int *p, char board[27][27])
{
	p[27] = (p[26] % 2 ? p[26] / 2 + 1 : p[26] / 2);
	while (!ft_solver(0, p, board))
		p[27]++;
}

/*
**	this function starts with reading
**	then validating
**	then fill-it
*/

int		main(int ac, char **av)
{
	int		pieces[28];
	char	board[27][27];

	//printf("strlen = %d", strlen("if (ft_isalpha(board[g_tet_tab[p][i + 1] + m[1]][g_tet_tab[p][i] + m[0]]))"));
	ft_memset((void*)pieces, -1, sizeof(int) * 27);
	if (ac == 2)
		if (!valid_read(0, 0, av, pieces))
		{
			ft_putstr("Error"); 
			exit (1);
		}
	
	//reset_board(board);
	if (pieces[0] != -1)
		ft_fill(pieces, board);
//****************************************************************//
	
	//printing empty board
	// testing functions
//	print_board(pieces[27], board);
//	print_piece();
//	for (int w = 0; w < 26; w++)
//		printf("%s\n", board[w]);
//	for (int i = 0; i < 26; i++)
//		printf("i = %d, %d\n", (i + 1) ,pieces[i]);
	return (0);
}, board)) == 0)
		{
			(p[27] > g_tet_tab[i][8] + m[0]) ? m[0]++ : 0;
			if (p[27] > g_tet_tab[i][9] + m[1]) 
			{
				m[0] = 0;
				m[1]++;
			}
		}
		if (val == 1)
			return (1);
	}
	return (1);
}

//	return (1) is complete
//	return (0) is not working
//	return (-1) increase board_size;
//	
int 	ft_solver(int i, int *p, char board[27][27])
{
	int var;
	int n;
	int m[2];

	n = 0; m[0] = 0; m[1] = 0;
	while (p[i] != -1)
	{
//		if (var = isvalid + place piece)
		if ((var = check_empty(p, i, m, board)) == 1)
		{
			ft_load(board, i, m, p);
			var = ft_solver(i + 1, p, board);
		}
		if (var == 0)
			ft_shit(board, i, m, p);
		if (var < 0)
			return (var);
	}
	return (2);
}

int 	ft_fill(int *p, char board[27][27])
{
	p[27] = (p[26] % 2 ? p[26] / 2 + 1 : p[26] / 2);
	while (!ft_solver(0, p, board))
		p[27]++;
}

/*
**	this function starts with reading
**	then validating
**	then fill-it
*/

int		main(int ac, char **av)
{
	int		pieces[28];
	char	board[27][27];

	//printf("strlen = %d", strlen("if (ft_isalpha(board[g_tet_tab[p][i + 1] + m[1]][g_tet_tab[p][i] + m[0]]))"));
	ft_memset((void*)pieces, -1, sizeof(int) * 27);
	if (ac == 2)
		if (!valid_read(0, 0, av, pieces))
		{
			ft_putstr("Error"); 
			exit (1);
		}
	
	//reset_board(board);
	if (pieces[0] != -1)
		ft_fill(pieces, board);
//****************************************************************//
	
	//printing empty board
	// testing functions
//	print_board(pieces[27], board);
//	print_piece();
//	for (int w = 0; w < 26; w++)
//		printf("%s\n", board[w]);
//	for (int i = 0; i < 26; i++)
//		printf("i = %d, %d\n", (i + 1) ,pieces[i]);
	return (0);
}