/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:23:00 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/05 18:17:24 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copying(unsigned char *pd, const unsigned char *ps, size_t n)
{
	size_t	i;

	i = 0;
	if (pd < ps)
	{
		while (i < n)
		{
			pd[i] = ps[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			pd[i - 1] = ps[i - 1];
			i--;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (const unsigned char *)src;
	ft_copying(pdest, psrc, n);
	return (dest);
}
