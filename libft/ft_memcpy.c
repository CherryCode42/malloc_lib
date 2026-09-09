/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:21:22 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 19:21:24 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	i = 0;
	pdest = dest;
	psrc = src;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}
