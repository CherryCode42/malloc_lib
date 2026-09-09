/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:18:26 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 19:18:26 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] != '\0' && i + j < len)
			{
				if (big[i + j] != little[j])
					break ;
				j++;
			}
			if (little[j] == '\0')
			{
				return ((char *)(big + i));
			}
		}
		i++;
	}
	return (NULL);
}
