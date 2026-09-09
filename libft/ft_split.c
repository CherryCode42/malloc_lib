/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:55:31 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/06 16:55:31 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char *str, char c)
{
	int	i;
	int	word;
	int	in_word;

	i = 0;
	word = 0;
	in_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && in_word == 0)
		{
			in_word = 1;
			word++;
		}
		else if (str[i] == c)
		{
			in_word = 0;
		}
		i++;
	}
	return (word);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = (char *)malloc(n + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s, n);
	str[n] = '\0';
	return (str);
}

static char	**ft_free_mem(char **res, size_t j)
{
	while (j > 0)
		free(res[--j]);
	free(res);
	return (NULL);
}

static char	**ft_splitting(char const *s, char **res, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			res[j] = ft_strndup(s + start, i - start);
			if (!res[j])
				return (ft_free_mem(res, j));
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_word((char *)s, c);
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_splitting(s, res, c);
	return (res);
}
