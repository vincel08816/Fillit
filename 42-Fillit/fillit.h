#ifndef FILLIT_H
# define FILLIT_H
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

/*
**	i, o, l. j, t, s, z
*/

typedef	struct	sad
{
	int			piece[19];
	int			permuation;
}				idk;


static int		g_tet_tab[19][8] = \
{
	{0,0,0,1,0,2,0,3},	//1
	{0,0,1,0,2,0,3,0},	//2

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
};

static int		g_pieces;

char	*something(char **av, idk **any);

#endif