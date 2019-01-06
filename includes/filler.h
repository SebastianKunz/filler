/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 09:59:20 by skunz             #+#    #+#             */
/*   Updated: 2019/01/05 21:52:06 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "map.h"
# include "libft.h"

typedef struct	s_filler {
	t_point		cords;
	char		sign;
}				t_filler;

typedef struct	s_global {
	t_board		board;
	t_piece		piece;
	t_filler	player;
	int			**heat;
	t_filler	enemy;
	t_point		offset;
}				t_global;

enum			e_error {
	e_none,
	e_malloc,
	e_open_file,
};

/*
** main.c
*/

void			ft_error(int code);
void			print_cords(t_point cords);

/*
** map.c
*/

void			get_player_number(t_global *global);

/*
** place.c
*/

int				ft_place(t_global g);

/*
** heat.c
*/

void			init_heat(t_global *g);

#endif
