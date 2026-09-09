/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:18:54 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 19:18:54 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_place;
	char		a;

	a = (char)c;
	last_place = NULL;
	while (*s != '\0')
	{
		if (*s == a)
		{
			last_place = s;
		}
		s++;
	}
	if (a == '\0')
		return ((char *)s);
	return ((char *)last_place);
}
