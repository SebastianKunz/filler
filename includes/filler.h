/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 09:59:20 by skunz             #+#    #+#             */
/*   Updated: 2019/01/03 13:24:08 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // delte
# include "map.h"
# include "libft.h"
# include "place.h"


typedef struct  s_global {
	t_board		board;
	t_piece		piece;
    t_filler	player;
	int			**heat;
    t_filler	enemy;
	t_point		closest;
}               t_global;

enum			e_error {
	e_none,
	e_malloc,
	e_open_file,
};


void	ft_error(int code);

void	get_player_number(t_global *global);
// void	find_places(t_global *g);
void	ft_place(t_global g);

t_point get_pos(t_point shape, t_point board);

void	init_heat(t_global *g);

#endif
