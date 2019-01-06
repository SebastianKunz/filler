/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:03:52 by skunz             #+#    #+#             */
/*   Updated: 2019/01/05 16:01:20 by skunz            ###   ########.fr       */
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

int		is_placeable(t_global *g, int b_y, int b_x)
{
	int	score;
	int	hits;
	int	y;
	int	x;
	int prev_bx;

	get_offset(g);
	y = g->offset.y - 1;
	hits = 0;
	score = 0;
	prev_bx = b_x;
	while (++y < g->piece.size.y)
	{
		x = g->offset.x - 1;
		// fprintf(stderr, "b_x is %d\n", b_x);
		// fflush(stderr);
		while (++x < g->piece.size.x)
		{
			// fprintf(stderr, "board y:%d x:%d\n", b_y, b_x);
			// fflush(stderr);
			if ((g->board.map[b_y][b_x] == g->enemy.sign || g->board.map[b_y][b_x] == ft_tolower(g->enemy.sign))&& g->piece.map[y][x] == '*')
				return (0);
			if (g->piece.map[y][x] == '*' && (g->board.map[b_y][b_x] == g->player.sign || g->board.map[b_y][b_x] == ft_tolower(g->player.sign)))
			{
				hits++;
				score += g->heat[b_y][b_x];
			}
			b_x++;
			if (b_x >= g->board.size.x)
				return (0);
		}
		b_x = prev_bx;
		if (b_x < 0)
			return (0);
			// b_x = (g->board.size.x - b_x * -1) -1;
		b_y++;
		if (b_y >= g->board.size.y)
			return (0);
	}
	if (hits == 1)
		return (score);
	return (0);
}

void	ft_place(t_global g)
{
	int y;
	int x;
	int	score;
	int prev_score;
	int set;
	t_point closest;

	y = -1;
	set = 0;
	prev_score = g.board.size.y + g.board.size.x;
	while (++y < g.board.size.y)
	{
		x = -1;
		while (++x < g.board.size.x)
		{
			// fprintf(stderr, "Trying y:%d x:%d\n", y, x);
			// fflush(stderr);
			if ((score = is_placeable(&g, y, x)))
			{
					// fprintf(stderr, "Offset y:%d x:%d\n", g.offset.y, g.offset.x);
					// fflush(stderr);
				if (score <= prev_score)
				{
					closest.x = x - g.offset.x;
					closest.y = y - g.offset.y;
					set = 1;
				}
				prev_score = score;
			}
		}
	}
	if (!set)
	{
		fprintf(stderr, "Could not find a place to fit the piece\n");
		exit (-1);
	}
	printf("%d %d\n", closest.y, closest.x);
	fprintf(stderr, "%d %d\n", closest.y, closest.x);

	fflush(stderr);
	fflush(stdout);

}