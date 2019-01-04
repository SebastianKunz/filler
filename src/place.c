/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:03:52 by skunz             #+#    #+#             */
/*   Updated: 2019/01/03 16:23:43 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		is_placeable(t_global g, int b_y, int b_x)
{
	int	score;
	int	hits;
	int	y;
	int	x;

	y = -1;
	hits = 0;
	score = 0;
	while (++y < g.piece.size.y)
	{
		x = -1;
		while (++x < g.piece.size.x)
		{
			// fprintf(stderr, "board y:%d x:%d\n", b_y, b_x);
			// fflush(stderr);
			if (g.board.map[b_y][b_x] == g.enemy.sign)
				return (0);
			if (g.piece.map[y][x] == '*' && g.board.map[b_y][b_x] == g.player.sign)
				hits++;
			if (g.piece.map[y][x] == '*' && g.heat[b_y][b_x] > 0)
				score += g.heat[b_y][b_x];
			b_x++;
			if (b_x > g.board.size.x - 1)
				return (0);
		}
		b_x -= x;
		if (b_x < 0)
			return (0);
		b_y++;
		if (b_y > g.board.size.y - 1)
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
			if ((score = is_placeable(g, y, x)))
			{
				if (score <= prev_score)
				{
					closest.x = x;
					closest.y = y;
					set = 1;
				}
				prev_score = score;


				// fprintf(stderr, "placeable at y:%d x:%d\n", y, x);
				// fflush(stderr);

				fprintf(stderr, "score: %d\n", score);
				fflush(stderr);
			}
		}
	}

	printf("%d %d\n", closest.y, closest.x);
	fflush(stdout);
	if (!set)
		exit (-1);
}