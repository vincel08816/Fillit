#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <math.h>
#include "fillit.h"

static const int		g_tet[19][10] = 
{
	{0,0,0,1,0,2,0,3,1,4},	//0
	{0,0,1,0,2,0,3,0,4,1},	// 1
	{0,0,1,0,0,1,1,1,2,2},	//2
	{0,0,0,1,0,2,1,2,2,3},	//3
	{0,0,1,0,2,0,0,1,3,2},	//4
	{0,0,1,0,1,1,1,2,2,3},	//5
	{2,0,0,1,1,1,2,1,3,2},	//6
	{1,0,1,1,0,2,1,2,2,3},	//7
	{0,0,0,1,1,1,2,1,3,2},	//8
	{0,0,1,0,0,1,0,2,2,3},	//9
	{0,0,1,0,2,0,2,1,3,2},	//10
	{1,0,0,1,1,1,2,1,3,2},	//11
	{0,0,0,1,1,1,0,2,2,3},	//12
	{0,0,1,0,2,0,1,1,3,2},	//13
	{1,0,0,1,1,1,1,2,2,3},	//14
	{1,0,2,0,0,1,1,1,3,2},	//15
	{0,0,0,1,1,1,1,2,2,3},	//16
	{0,0,1,0,1,1,2,1,3,2},	//17
	{1,0,0,1,1,1,0,2,2,3}	//18
};

//			uses square roots to find board size
//			adds one if modulus exists since integer rounds down

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

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

int			board_size(int pc)
{
	int n;		//square roots

	if (pc <= 0)
		return (0);
	n = 1;
	while ((n + 1) * (n + 1) < (pc * 4))
		n++;
	if ((n * n) % (pc * 4))
		n++;
	return (n);
}

//			fills the 2-D board with '.' if size isn't 0
//			fills 2-D array with 'A's if it is
void		reset_board(int size, char board[27][27])
{
	int k;
	int j;

	k = -1;
	if (size <= 0)
	{
		while (++k < 27)
		{
			j = -1;
			while (++j < 27)
				board[k][j] = 'A';
		}
		return ;
	}
	while (++k < size)
	{
		j = -1;
		while (++j < size)
			board[k][j] = '.';
	}
}

//		prints the board
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

int		load_p(int i, int *m, int *p, char board[27][27])
{
	board[g_tet[p[i]][1] + m[1]][g_tet[p[i]][0] + m[0]] = i + 'A';
	board[g_tet[p[i]][3] + m[1]][g_tet[p[i]][2] + m[0]] = i + 'A';
	board[g_tet[p[i]][5] + m[1]][g_tet[p[i]][4] + m[0]] = i + 'A';
	board[g_tet[p[i]][7] + m[1]][g_tet[p[i]][6] + m[0]] = i + 'A';

	/********** testing print **************/
//	printf("load m[0]: %d , m[1] : %d\n", m[0], m[1]);
//	printf("Piece Queue :	");
//	for (int d = i ; d < 28; d++)
//		printf("%d  ", p[d]);
//	print_board(p[27], board);
//	printf("%d", p[26]);
	//print_board(p[27] + 1, board);
	//print_board(27, board);
}

//		remove piece
int		rm_p(int i, int *m, int *p, char board[27][27])
{
	board[g_tet[p[i]][1] + m[1]][g_tet[p[i]][0] + m[0]] = '.';
	board[g_tet[p[i]][3] + m[1]][g_tet[p[i]][2] + m[0]] = '.';
	board[g_tet[p[i]][5] + m[1]][g_tet[p[i]][4] + m[0]] = '.';
	board[g_tet[p[i]][7] + m[1]][g_tet[p[i]][6] + m[0]] = '.';


	/********** testing print **************/
//	printf("remove m[0]: %d , m[1] : %d\n", m[0], m[1]);
//	printf("Piece Queue :	");
//	for (int d = i ; d < 28; d++)
//		printf("%d  ", p[d]);
//	print_board(p[27], board);
//		printf("%d", p[26]);
	//print_board(p[27] + 1, board);
	//print_board(27, board);
}

//		this function returns:
// 			 0 	if characters are alpha
//			 1 	if space is found
//			-1 	if exceeds space boundaries
int		open_space(int i, int *m, int *p, char board[27][27])
{
	int n;

	n = 0;
	if (m[1] > p[27])
		return (-1);
	while (n < 8)
	{
//		if it is an alphabet character, 
//		that means it hit another piece or boundary
		if (ft_isalpha(board[g_tet[p[i]][n + 1] + \
		m[1]][g_tet[p[i]][n] + m[0]]))
			return (0);
		n += 2;
	}
	return (1);
}

//		increases m[0] or m[1];
void 	increase_m(int i, int *m, int *p, char board[27][27])
{
	if (m[0] < p[27]) // m[0] < 27)
		m[0]++;
	else //if (m[1] < 27)
	{
		m[0] = 0;
		m[1]++;
	}
}

//		returns 1 if there are spaces available
//		returns 0 if there are no more spaces

int		all_space(int i, int *m, int *p, char board[27][27])
{
	int ret_o;

	while ((ret_o = open_space(i, m, p, board)) == 0)
		increase_m(i, m, p, board);
	if (ret_o == -1)
		return (0);
	return (1);
}

//		returns 1 when complete
//		returns 0 when I need to move the piece 
//		if it returns 0 to fillit, then increase board size
//		p is the piece array
//		i is the index of the piece array

int		ft_solver(int i, int *p, char board[27][27])
{
	int m[2];	//m[0] is the shift on the x and m[1] is the shift on y
	int ret;	//what is being returned by solver
	int c_ret;

	ret = 0; m[0] = 0; m[1] = 0;

	// when there are no pieces to fit
	if (p[i] == -1 || i >= 26)
		return (1);
//	loop for checking if there is any space left the piece on the board;
//		if the piece passes, go use the solver on the next piece
//		if solver passes, break the loop and return 1;
//		if the next solver fails, remove the piece then go to the next available space and repeat loop
	while (all_space(i, m, p, board) && ret == 0)
	{
		//if the space is valid and loads piece in if it's valid
		if (open_space(i, m, p, board))
		{
			load_p(i, m, p, board);
			if (ft_solver(i + 1, p, board))	//solve next piece
				return (1);
			if (ret == 0)	// if the solver eventually fails
			{
				rm_p(i, m, p, board);
				increase_m(i, m, p, board);	//increment m[0] or [m1];
			}
		}
	}
	// no spaces left
	if (!(all_space(i, m, p, board)))
		return (0);
	return (1);
}

//		pre-recursion, function that increases the size
int		ft_fill(int *p, char board[27][27])
{
	p[27] = board_size(p[26]);
	reset_board(p[27], board);
	if (p[0] != -1)
		while (!ft_solver(0, p, board))
		{
			p[27]++;
			reset_board(p[27], board);
//			p[27] is the size	for (int i = 1; i < 27; i++)
//			printf("%d", p[27		printf("i = %d, b = %d\n, b_real = %f ", i , board_size(i);
		}
	return (1);
}

//p[0-25] are pieces with their corresponding indices
//p[26] is the piece count
//p[27] is the board size;
//board is actually passed along throughout the functions

int		main(int ac, char **av)
{
	int		pieces[28];
	char	board[27][27];

	ft_memset((void*)pieces, -1, sizeof(int) * 27);
	if (ac == 2)
	{
		if (!valid_read(0, 0, av, pieces))
		{
			ft_putstr("Error"); 
			exit (1);
		}
	}
	//printf("%d, %d", pieces[26], pieces[27]);
	reset_board(0, board);
	printf("%d", pieces[26]);
	ft_fill(pieces, board);
	print_board(pieces[27], board);
//	printf("{");
//	for (int i = 0; i < 28; i++)
//	{
//		printf("-1,", i);
//	}
//	printf("};\n\n\n");


	//**************board_size test************************\//
//	for (int i = 1; i < 27; i++)
//		printf("i = %d, b = %d\n", i , board_size(i);
}