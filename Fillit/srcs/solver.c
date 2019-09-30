/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:08:04 by vilee             #+#    #+#             */
/*   Updated: 2019/09/29 15:08:05 by vilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**		this function returns:
** 			 0 	if a character is alpha
**			 1 	if spot is found
**			-1 	if exceeds boundaries
*/

int		open_space(int i, int *m, int *p, char board[27][27])
{
	int n;

	n = 0;
	if (m[1] > p[27])
		return (-1);
	while (n < 8)
	{
		if (ft_isalpha(board[g_tet[p[i]][n + 1] + \
		m[1]][g_tet[p[i]][n] + m[0]]))
			return (0);
		n += 2;
	}
	return (1);
}

/*
**		increases m[0] or m[1];
*/

void	increase_m(int *m, int *p)
{
	if (m[0] < p[27])
		m[0]++;
	else
	{
		m[0] = 0;
		m[1]++;
	}
}

/*
**		returns 1 if there are spaces available
**		returns 0 if there are no more spaces
*/

int		all_space(int i, int *m, int *p, char board[27][27])
{
	int ret_o;

	while ((ret_o = open_space(i, m, p, board)) == 0)
		increase_m(m, p);
	if (ret_o == -1)
		return (0);
	return (1);
}

/*
**		returns 1 when complete
**		returns 0 when I need to move the piece
**		** Variables **
**		if it returns 0 to fillit, then increase board size
**		p is the piece array
**		i is the index of the piece array
**		m[0] is the shift on the x and m[1] is the shift on y
**		***********************************************************
**	loop for checking if there is any space left the piece on the board;
**		if the piece passes, go use the solver on the next piece
**		if solver passes, break the loop and return 1;
**		if the next solver fails,
**		remove the piece then go to the next available space and repeat loop
*/

int		ft_solver(int i, int *p, char board[27][27])
{
	int		m[2];
	size_t	ret;

	m[1] = 0;
	set_zero(&ret, (size_t*)&m, 0, 0);
	if (p[i] == -1 || i >= 26)
		return (1);
	while (all_space(i, m, p, board) && ret == 0)
	{
		if (open_space(i, m, p, board))
		{
			load_p(i, m, p, board);
			if ((ret = (ft_solver(i + 1, p, board)) == 1))
				return (1);
			if (ret == 0)
			{
				rm_p(i, m, p, board);
				increase_m(m, p);
			}
		}
	}
	if (!(all_space(i, m, p, board)))
		return (0);
	return (1);
}

/*
**		p[26] is the piece count
**		p[27] is the board size
**		if p[0] == -1 that means the piece doesn't not exist
**		pre-recursion, function that increases the size
*/

int		ft_fill(int *p, char board[27][27])
{
	p[27] = board_size(p[26]);
	reset_board(p[27], board);
	if (p[0] != -1)
		while (!ft_solver(0, p, board))
		{
			p[27]++;
			reset_board(p[27], board);
		}
	return (1);
}
