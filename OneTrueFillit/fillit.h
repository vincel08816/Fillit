#ifndef FILLIT_H
# define FILLIT_H
# include "libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/*
**	i, o, l. j, t, s, z
**	{x1,y1,x2,y2,x3,y3,x4,y4}
**	2 extra for [length] then [height] (unused lol)
*/

static const int	g_tet[19][10] = 
{
	{0,0,0,1,0,2,0,3,1,4},
	{0,0,1,0,2,0,3,0,4,1},
	{0,0,1,0,0,1,1,1,2,2},
	{0,0,0,1,0,2,1,2,2,3},
	{0,0,1,0,2,0,0,1,3,2},
	{0,0,1,0,1,1,1,2,2,3},
	{2,0,0,1,1,1,2,1,3,2},
	{1,0,1,1,0,2,1,2,2,3},
	{0,0,0,1,1,1,2,1,3,2},
	{0,0,1,0,0,1,0,2,2,3},
	{0,0,1,0,2,0,2,1,3,2},
	{1,0,0,1,1,1,2,1,3,2},
	{0,0,0,1,1,1,0,2,2,3},
	{0,0,1,0,2,0,1,1,3,2},
	{1,0,0,1,1,1,1,2,2,3},
	{1,0,2,0,0,1,1,1,3,2},
	{0,0,0,1,1,1,1,2,2,3},
	{0,0,1,0,1,1,2,1,3,2},
	{1,0,0,1,1,1,0,2,2,3}
};

/*
**		Read and Validation part
*/

int					valid_string(char *s);
int					shift2(int i, int diff1, int k, int *validate);
int					shift(size_t i, size_t j, int *validate, char *ptr[]);
int 				valid_read2(int *p, char *b, size_t len, size_t i);
int					valid_read(size_t i, int fd, char **av, int *pieces);

/*
**		Auxiliary Board Functions
*/

void				reset_board(int size, char board[27][27]);
void				print_board(int size, char board[27][27]);
void				load_p(int i, int *m, int *p, char board[27][27]);
void				rm_p(int i, int *m, int *p, char board[27][27]);

/*
**		Board Functions
*/

void 				increase_m(int *m, int *p);
int					board_size(int pc);
int					all_space(int i, int *m, int *p, char board[27][27]);
int					ft_solver(int i, int *p, char board[27][27]);
int					ft_fill(int *p, char board[27][27]);

#endif