/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 09:59:20 by skunz             #+#    #+#             */
/*   Updated: 2019/01/01 12:38:16 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // delte
# include "map.h"
# include "libft.h"


typedef struct  s_global {
	t_board		board;
	t_piece		piece;
}               t_global;

enum			e_error {
	e_none,
	e_malloc,
	e_open_file,
};


void	ft_error(int code);

void	get_player_number(char *player_num);

#endif
