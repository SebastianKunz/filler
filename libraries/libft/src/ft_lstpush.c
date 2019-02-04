/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <skunz@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 16:35:54 by skunz             #+#    #+#             */
/*   Updated: 2019/01/02 16:45:56 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **begin, void const *content, size_t content_size)
{
	t_list *current;

	current = *begin;
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = ft_lstnew(content, content_size);
	}
	else
		*begin = ft_lstnew(content, content_size);
}
