/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:20:11 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 19:20:11 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	l_src;
	size_t	l_dest;
	size_t	len;

	i = 0;
	l_src = ft_strlen(src);
	l_dest = ft_strlen(dest);
	if (size <= l_dest)
		return (l_src + size);
	else
	{
		while (i + l_dest < size - 1 && src[i] != '\0')
		{
			dest[l_dest + i] = src[i];
			i++;
		}
		dest[l_dest + i] = '\0';
	}
	len = l_src + l_dest;
	return (len);
}
