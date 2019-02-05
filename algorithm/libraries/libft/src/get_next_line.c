/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:20:08 by skunz             #+#    #+#             */
/*   Updated: 2019/02/04 19:12:45 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_stock_the_new_line(char *str)
{
	int			i;
	int			len;
	char		*new;

	i = 0;
	len = 0;
	while (str[len++])
		;
	if (!(new = (char *)malloc(sizeof(*new) * len + 1)))
		return (NULL);
	while (i < len && str[i] != '\n')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char		*ft_clean_new(char *str)
{
	char		*new;
	int			i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if ((str[i] && !str[i + 1]) || !str[i])
	{
		ft_strdel(&str);
		return (NULL);
	}
	new = ft_strdup(str + i + 1);
	ft_strdel(&str);
	return (new);
}

int				get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static char	*new;

	if (!new)
		new = ft_strnew(1);
	if (BUFF_SIZE < 0 || !line || fd > MAX_FD || fd < 0)
		return (-1);
	ret = 2;
	while (!(ft_strchr(new, '\n')))
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		new = ft_strjoin(new, buff);
		if (ret == 0 && *new == '\0')
			return (0);
		if (ret == 0)
			break ;
	}
	*line = ft_stock_the_new_line(new);
	new = ft_clean_new(new);
	return (1);
}
