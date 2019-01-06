/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 20:07:25 by skunz             #+#    #+#             */
/*   Updated: 2019/01/05 20:09:07 by skunz            ###   ########.fr       */
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

int		main(void)
{
	t_global	global;

	get_player_number(&global);
	while (1)
	{
		get_board(&global.board);
		get_piece(&global.piece);
		init_heat(&global);
		if (!ft_place(global))
		{
			free_global(&global);
			return (0);
		}
		free_global(&global);
	}
	return (0);
}
