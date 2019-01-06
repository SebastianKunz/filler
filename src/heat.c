/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 10:29:28 by skunz             #+#    #+#             */
/*   Updated: 2019/01/05 19:54:13 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	set_zeros(t_global *g)
{
	int	y;
	int	x;

	y = -1;
	while (++y < g->board.size.y)
	{
		x = -1;
		while (++x < g->board.size.x)
		{
			if (g->heat[y][x] == 0)
				g->heat[y][x] = g->board.size.y + g->board.size.x;
		}
	}
}

void	set_first(t_global *g)
{
	int	y;
	int	x;

	y = -1;
	while (++y < g->board.size.y)
	{
		x = -1;
		while (++x < g->board.size.x)
		{
			if (g->heat[y][x] == -2)
				;
			else if (x < g->board.size.x - 1 && g->heat[y][x + 1] == -2)
				g->heat[y][x] = 1;
			else if (y < g->board.size.y - 1 && g->heat[y + 1][x] == -2)
				g->heat[y][x] = 1;
			else if (x > 0 && g->heat[y][x - 1] == -2)
				g->heat[y][x] = 1;
			else if (y > 0 && g->heat[y - 1][x] == -2)
				g->heat[y][x] = 1;
		}
	}
}

void	set_neighbor(t_global *g)
{
	int	y;
	int	x;
	int i;

	i = 0;
	while (++i < g->board.size.x + g->board.size.y)
	{
		y = -1;
		while (++y < g->board.size.y)
		{
			x = -1;
			while (++x < g->board.size.x)
				if (g->heat[y][x] == 0)
				{
					if (x < g->board.size.x - 1 && g->heat[y][x + 1] == i)
						g->heat[y][x] = i + 1;
					else if (y < g->board.size.y - 1 && g->heat[y + 1][x] == i)
						g->heat[y][x] = i + 1;
					else if (x > 0 && g->heat[y][x - 1] == i)
						g->heat[y][x] = i + 1;
					else if (y > 0 && g->heat[y - 1][x] == i)
						g->heat[y][x] = i + 1;
				}
		}
	}
}

void	set_value(t_global *g, int y)
{
	int	x;

	x = -1;
	while (++x < g->board.size.x)
	{
		if (g->board.map[y][x] == g->player.sign ||
			g->board.map[y][x] == ft_tolower(g->player.sign))
			g->heat[y][x] = -1;
		else if (g->board.map[y][x] == g->enemy.sign ||
			g->board.map[y][x] == ft_tolower(g->enemy.sign))
			g->heat[y][x] = -2;
		else
			g->heat[y][x] = 0;
	}
}

void	init_heat(t_global *g)
{
	int	y;

	y = -1;
	if (!(g->heat = malloc(sizeof(int*) * g->board.size.y)))
		ft_error(e_malloc);
	while (++y < g->board.size.y)
	{
		if (!(g->heat[y] = malloc(sizeof(int) * g->board.size.x)))
			ft_error(e_malloc);
		set_value(g, y);
	}
	set_first(g);
	set_neighbor(g);
	set_zeros(g);
}
