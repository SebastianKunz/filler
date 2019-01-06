/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 10:28:56 by skunz             #+#    #+#             */
/*   Updated: 2019/01/05 20:16:20 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct	s_point {
	int			x;
	int			y;
}				t_point;

typedef struct	s_filler {
	t_point		cords;
	char		sign;
}				t_filler;

typedef struct	s_board {
	char		**map;
	t_point		size;
}				t_board;

typedef	struct	s_piece {
	t_point		size;
	char		**map;
	int			stars;
}				t_piece;

void			get_board(t_board *board);
void			get_piece(t_piece *piece);

#endif
