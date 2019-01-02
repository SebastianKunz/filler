/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 09:45:10 by skunz             #+#    #+#             */
/*   Updated: 2019/01/01 15:21:22 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_error(int code)
{
	if (code == 1)
		ft_putstr("malloc failed\n");
	else if (code == 2)
		ft_putstr("failed to open file\n");
	exit(code);
}

void	print_pos(t_point shape, t_point board)
{
	t_point offset;

	offset.x = 0;
	offset.y = 0;
	while (shape.x-- > 0)
		offset.x++;
	while (shape.y-- > 0)
		offset.y++;
	ft_putnbr(board.y - offset.y);
	ft_putchar(' ');
	ft_putnbr(board.x - offset.x);
	ft_putchar('\n');
}

void	get_my_pos(t_board *board, char sign)
{
	int	y;
	int	x;
	char is_first;

	y = -1;
	is_first = -1;
	while (++y < board->size.y - 1 && is_first != 42)
	{
		x = -1;
		while (++x < board->size.x)
		{
			if ((board->map[y][x] == 'x' || board->map[y][x] == 'X') && is_first == -1)
				is_first = 'X';
			else if ((board->map[y][x] == 'o' || board->map[y][x] == 'O') && is_first == -1)
				is_first = 'O';
			if ((board->map[y][x] == ft_tolower(sign) || board->map[y][x] == sign) && sign == is_first)
			{
				board->player.x = x;
				board->player.y = y;
			}
			else if ((board->map[y][x] == ft_tolower(sign) || board->map[y][x] == sign) && sign != is_first)
			{
				board->player.x = x;
				board->player.y = y;
				is_first = 42;
				break ;
			}
		}
	}
}

t_point	get_shape_pos(t_piece piece)
{
	t_point cords;
	int y;
	int x;

	y = -1;
	cords.x = 0;
	cords.y = 0;
	while (++y < piece.size.y)
	{
		x = -1;
		while (++x < piece.size.x)
		{
			if (piece.map[y][x] == '*')
			{
				cords.x = x;
				cords.y = y;
				return (cords);
			}
		}
	}
	return (cords);
}

void	free_global(t_global *global)
{
	ft_free2d(global->board.map, global->board.size.y - 1);
	ft_free2d(global->piece.map, global->piece.size.y - 1);
}

int main()
{
	t_global	global;

	get_player_number(&global.board.player_num);
	while (1)
	{
		get_board(&global.board);
		get_piece(&global.piece);
		get_my_pos(&global.board, global.board.player_num);
		t_point shape = get_shape_pos(global.piece);
		print_pos(shape, global.board.player);
		free_global(&global);
		// fprintf(stderr, "player: x:%d y:%d\n", global.board.player.x, global.board.player.y);
		// fprintf(stderr, "enemy: x:%d y:%d\n", global.board.enemy.x, global.board.enemy.y);
	}
	return (0);
}

