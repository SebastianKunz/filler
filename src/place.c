/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:03:52 by skunz             #+#    #+#             */
/*   Updated: 2019/01/05 21:51:35 by skunz            ###   ########.fr       */
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

int		is_free(t_global g, int b_y, int b_x, char sign)
{
	if (sign == -2)
		return (g.board.map[b_y][b_x] != g.enemy.sign &&
		g.board.map[b_y][b_x] != ft_toupper(g.enemy.sign));
	else if (sign == -1)
		return (g.board.map[b_y][b_x] != g.player.sign &&
			g.board.map[b_y][b_x] != ft_toupper(g.player.sign));
	else
		return (42);
}

int		is_placeable(t_global *g, int b_y, int b_x)
{
	t_point	i;
	int		score;
	int		hits;

	score = 0;
	hits = 0;
	i.y = g->offset.y - 1;
	while (++i.y < g->piece.size.y)
	{
		i.x = g->offset.x - 1;
		while (++i.x < g->piece.size.x)
		{
			if (!is_free(*g, b_y, b_x, -2) && g->piece.map[i.y][i.x] == '*')
				return (0);
			if (g->piece.map[i.y][i.x] == '*' && !is_free(*g, b_y, b_x, -1))
				hits++;
			(g->piece.map[i.y][i.x] == '*') ? score += g->heat[b_y][b_x] : (0);
			if (++b_x >= g->board.size.x)
				return (0);
		}
		b_x -= g->piece.size.x - g->offset.x;
		if (++b_y >= g->board.size.y)
			return (0);
	}
	return (score = (hits == 1) ? score : 0);
}

int		ft_place(t_global g)
{
	t_point	closest;
	int		y;
	int		x;
	int		score;
	int		lowest_score;

	y = -1;
	lowest_score = INT_MAX;
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
	if (lowest_score == INT_MAX)
		return (0);
	print_cords(closest);
	return (1);
}
