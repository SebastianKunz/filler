/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:03:52 by skunz             #+#    #+#             */
/*   Updated: 2019/01/05 20:41:48 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_offset(t_global *g)
{
	int y;
	int x;
	int min_x;
	int min_y;

	y = -1;
	min_x = g->piece.size.x;
	min_y = g->piece.size.y;
	while (++y < g->piece.size.y)
	{
		x = -1;
		while (++x < g->piece.size.x)
		{
			if (g->piece.map[y][x] == '*' && x < min_x)
				min_x = x;
			if (g->piece.map[y][x] == '*' && y < min_y)
				min_y = y;
		}
	}
	g->offset.x = min_x;
	g->offset.y = min_y;
}

// void	ft_check(t_global *g, int b_y, int b_x, int *hits)
// {
// 	if ((g->board.map[b_y][b_x] == g->enemy.sign ||
// 		g->board.map[b_y][b_x] == ft_tolower(g->enemy.sign)) &&
// 			g->piece.map[y][x] == '*')
// 		return (0);
// 	if (g->piece.map[y][x] == '*' &&
// 		(g->board.map[b_y][b_x] == g->player.sign ||
// 			g->board.map[b_y][b_x] == ft_tolower(g->player.sign)))
// 		*hits++;
// }

int		is_placeable(t_global *g, int b_y, int b_x)
{
	int	score;
	int	hits;
	int	y;
	int	x;

	score = 0;
	hits = 0;
	y = g->offset.y - 1;
	while (++y < g->piece.size.y)
	{
		x = g->offset.x - 1;
		while (++x < g->piece.size.x)
		{
			if ((g->board.map[b_y][b_x] == g->enemy.sign ||
				g->board.map[b_y][b_x] == ft_tolower(g->enemy.sign)) &&
					g->piece.map[y][x] == '*')
				return (0);
			if (g->piece.map[y][x] == '*' &&
				(g->board.map[b_y][b_x] == g->player.sign ||
					g->board.map[b_y][b_x] == ft_tolower(g->player.sign)))
				hits++;
			if (g->piece.map[y][x] == '*')
				score += g->heat[b_y][b_x];
			if (++b_x >= g->board.size.x)
				return (0); //implement crossover
		}
		b_x -= g->piece.size.x - g->offset.x;
		if (++b_y >= g->board.size.y)
			return (0); //implement crossover
	}
	score = (hits == 1) ? score : 0;
	return (score);
}

int		ft_place(t_global g)
{
	t_point	closest;
	int		y;
	int		x;
	int		score;
	int		lowest_score;

	y = -1;
	lowest_score = 2147483647;
	get_offset(&g);
	while (++y < g.board.size.y)
	{
		x = -1;
		while (++x < g.board.size.x)
			if ((score = is_placeable(&g, y, x)))
				if (score <= lowest_score)
				{
					closest.x = x - g.offset.x;
					closest.y = y - g.offset.y;
					lowest_score = score;
				}
	}
	if (lowest_score == 2147483647)
		return (0);
	print_cords(closest);
	return (1);
}
