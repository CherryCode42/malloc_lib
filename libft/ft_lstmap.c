/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:41:50 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 16:41:50 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;
	t_list	*buff;

	new_list = NULL;
	buff = lst;
	if (!lst || !f)
		return (NULL);
	while (buff)
	{
		new_elem = ft_lstnew(f(buff->content));
		if (!new_elem)
		{
			ft_lstclear(&new_list, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		buff = buff->next;
	}
	return (new_list);
}
