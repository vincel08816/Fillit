#include "fillit.h"
/*
**		fills the 2-D size with '.' if size isn't 0
**		fills 2-D array with 'A's otherwise
*/

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

/*
**		prints the board
*/

void	print_board(int size, char board[27][27])
{
	int k;

	k = -1;
	while (++k < size)
	{
		write(1, board[k], size);
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

/*
**		loads piece onto the board
**		p[i] is the current piece index
**		g_tet is the global table which the coordiantes are stored
**		m[1] is the shift in y and m[0] is the shift in x
*/

void	load_p(int i, int *m, int *p, char board[27][27])
{
	board[g_tet[p[i]][1] + m[1]][g_tet[p[i]][0] + m[0]] = i + 'A';
	board[g_tet[p[i]][3] + m[1]][g_tet[p[i]][2] + m[0]] = i + 'A';
	board[g_tet[p[i]][5] + m[1]][g_tet[p[i]][4] + m[0]] = i + 'A';
	board[g_tet[p[i]][7] + m[1]][g_tet[p[i]][6] + m[0]] = i + 'A';
}

/*
**		remove piece onto the board
**		p[i] is the current piece index
**		g_tet is the global table which the coordiantes are stored
**		m[1] is the shift in y and m[0] is the shift in x
*/

void	rm_p(int i, int *m, int *p, char board[27][27])
{
	board[g_tet[p[i]][1] + m[1]][g_tet[p[i]][0] + m[0]] = '.';
	board[g_tet[p[i]][3] + m[1]][g_tet[p[i]][2] + m[0]] = '.';
	board[g_tet[p[i]][5] + m[1]][g_tet[p[i]][4] + m[0]] = '.';
	board[g_tet[p[i]][7] + m[1]][g_tet[p[i]][6] + m[0]] = '.';
}