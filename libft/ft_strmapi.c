/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:18:12 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 19:18:12 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	len_s;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	result = (char *)malloc(len_s + 1);
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len_s] = '\0';
	return (result);
}
