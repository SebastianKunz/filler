/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 10:28:54 by skunz             #+#    #+#             */
/*   Updated: 2019/01/01 15:45:13 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_player_number(char *player_num)
{
	char	*line;
	char	ret;

	if((ret = get_next_line(0, &line)) == -1)
		ft_error(e_open_file);
	if (ft_strstr(line, "p1"))
		*player_num = 'O';
	else
		*player_num = 'X';
	free(line);
}


void	get_size(t_point *size)
{
	char	*line;
	char	ret;
	char	**info;

	if ((ret = get_next_line(0, &line) == -1))
		ft_error(e_open_file);
	fprintf(stderr, "%s\n", line);
	info = ft_strsplit(line, ' ');
	size->x = ft_atoi(info[2]);
	size->y = ft_atoi(info[1]);
	ft_free2d(info, 3);
	free(line);
}

void	get_piece(t_piece *piece)
{
	char *line;
	int		y;

	y = -1;
	get_next_line(0, &line);
	get_size(&piece->size);
	if (!(piece->map = malloc(sizeof(char*) * piece->size.y)))
		ft_error(e_malloc);
	while (++y < piece->size.y)
	{
		get_next_line(0, &line);
		piece->map[y] = ft_strdup(line);
		free(line);
	}
}

void	get_board(t_board *board)
{
	char	*line;
	int		y;

	y = -1;
	get_size(&board->size);
	if(!(board->map = malloc(sizeof(char*) * board->size.y)))
		ft_error(e_malloc);
	while (++y < board->size.y)
	{
		get_next_line(0, &line);
		if (y > 0 && y < board->size.y + 1)
			board->map[y - 1] = ft_strdup(line + 4);
		free(line);
	}
}