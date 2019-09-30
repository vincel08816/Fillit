/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:14:48 by vilee             #+#    #+#             */
/*   Updated: 2019/09/29 15:14:51 by vilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	p[0-25] are pieces with their corresponding indices
**	p[26] is the piece count
**	p[27] is the board size;
**	board is actually passed along throughout the functions
*/

int		main(int ac, char **av)
{
	int		pieces[28];
	char	board[27][27];

	ft_memset((void*)pieces, -1, sizeof(int) * 27);
	if (ac == 2)
	{
		if (!valid_read(0, 0, av, pieces))
		{
			ft_putstr("error\n");
			exit(1);
		}
	}
	else
	{
		ft_putstr("error\n");
		exit(1);
	}
	reset_board(0, board);
	ft_fill(pieces, board);
	print_board(pieces[27], board);
	return (0);
}
