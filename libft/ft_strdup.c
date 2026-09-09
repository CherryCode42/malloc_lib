/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:20:28 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 19:20:30 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len_s;
	char	*dup;

	len_s = ft_strlen(s);
	dup = malloc (len_s + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len_s);
	dup[len_s] = '\0';
	return (dup);
}
