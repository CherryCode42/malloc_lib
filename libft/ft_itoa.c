/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:28:57 by iarefeva          #+#    #+#             */
/*   Updated: 2024/06/05 18:06:22 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static char	*ft_min_0_max(int n)
{
	if (n == 0)
		return ("0");
	else if (n == -2147483648)
		return ("-2147483648");
	else if (n == 2147483647)
		return ("2147483647");
	else
		return (NULL);
}

static char	*ft_res(int len, int n)
{
	char	*res;
	int		unsigned_num;
	int		i;

	unsigned_num = n;
	if (n < 0)
	{
		len++;
		unsigned_num *= -1;
	}
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	i = len - 1;
	while (unsigned_num)
	{
		res[i--] = unsigned_num % 10 + '0';
		unsigned_num /= 10;
	}
	if (n <= 0)
		res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		num;
	int		len;

	len = 0;
	num = n;
	if (ft_min_0_max(n))
	{
		return (ft_strdup(ft_min_0_max(n)));
	}
	if (n < 0)
		num = n * -1;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	res = ft_res(len, n);
	if (!res)
		return (NULL);
	return (res);
}

/*int	main()
{
	printf("%s\n", ft_itoa(42));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(0));
	return (0);
}*/