/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 09:45:10 by skunz             #+#    #+#             */
/*   Updated: 2019/01/02 16:0:48 by skunz            ###   ########.fr       */
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

t_point get_pos(t_point shape, t_point board)
{
	t_point offset;
	t_point ret;

	offset.x = 0;
	offset.y = 0;
	while (shape.x-- > 0)
		offset.x++;
	while (shape.y-- > 0)
		offset.y++;
	ret.y = board.y - offset.y;
	ret.x = board.x - offset.x;
	return (ret);
}



// void	get_closest_piece(t_board *board)
// {
// 	int y;
// 	int x;

// 	y = -1;
// 	board->closest.x = board->size.x;
// 	board->closest.y = board->size.y;
// 	while (++y < board->size.y)
// 	{
// 		x = -1;
// 		while (++x < board->size.x)
// 		{
// 			if (board->map[x][y] == board->player_num || board->map[y][x] == ft_tolower(board->player_num))
// 			{
// 				if (ABS(x - board->enemy.x) < board->closest.x)
// 					board->closest.x = x;
// 				if (ABS(y - board->enemy.y) < board->closest.y)
// 					board->closest.y = y;
// 			}
// 		}
// 	}
// }

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

void	print_cords(t_point cords)
{
	ft_putnbr(cords.y);
	ft_putchar(' ');
	ft_putnbr(cords.x);
	ft_putchar('\n');
}

void	free_global(t_global *global)
{
	ft_free2d((void**)global->board.map, global->board.size.y);
	ft_free2d((void**)global->piece.map, global->piece.size.y);
	ft_free2d((void**)global->heat, global->board.size.y);
}

void	ft_print_info(t_global global)
{
	fprintf(stderr, "Board size: y:%d x:%d\n", global.board.size.y, global.board.size.x);
	fprintf(stderr, "Piece size: y:%d x:%d\n", global.piece.size.y, global.piece.size.x);
}

int main()
{
	t_global	global;

	get_player_number(&global);
	while (1)
	{
		get_board(&global.board);
		get_piece(&global.piece);
		init_heat(&global);

		for (int y = 0; y < global.board.size.y; y++)
		{
			for (int x = 0; x < global.board.size.x; x++)
			{
				fprintf(stderr, "%2d ", global.heat[y][x]);
				fflush(stderr);
			}
			fprintf(stderr, "\n");
			fflush(stderr);
		}

		ft_place(global);
		free_global(&global);




		// ft_print_info(global);
		// find_places(&global);
		// t_point *test2;
		// t_list *begin;
		// begin = global.places;
		// while (global.places)
		// {
		// 	test2 = global.places->content;
		// 	fprintf(stderr, "possible: [%d] [%d]\n", test2->y, test2->x);
		// 	fflush(stderr);
		// 	global.places = global.places->next;
		// }
		// global.places = begin;
		// test2 = global.places->content;
		// print_cords(*test2);
		// printf("%d %d\n", 2, 1);
		// fflush(stdout);
	}
	// while (1);
	return (0);
}

