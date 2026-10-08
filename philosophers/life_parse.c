/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:58:21 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/20 15:13:22 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *nbr)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while (nbr[i] == ' ' || (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	if (nbr[i] == '+')
		i++;
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		number = (number * 10) + (nbr[i] - '0');
		i++;
	}
	return (number);
}

static int	is_positive_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

static int	check_arg(char *arg)
{
	if (ft_strlen(arg) > 10)
	{
		print_error("Your args is too long.");
		printf("It shouldn't be more than 2147483647!\n");
		return (1);
	}
	if (!is_positive_nbr(arg))
	{
		print_error("There is a wrong symbol in the arguments");
		return (1);
	}
	return (0);
}

int	check_correct_imput(long nbr, long to_die, long to_eat, long to_sleep)
{
	if (to_die > 2147483647 || to_eat > 2147483647
		|| nbr > 2147483647 || to_sleep > 2147483647)
	{
		print_error("Imput number shouldn't be more than 2147483647");
		return (1);
	}
	if (to_die < 60 || to_eat < 60
		|| to_sleep < 60)
	{
		print_error("Time shouldn't be less than 60ms");
		return (1);
	}
	return (0);
}

int	life_parse(char	**argv, t_philo_life *life)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (check_arg(argv[i]))
			return (1);
		i++;
	}
	life->nbr_of_philos = ft_atol(argv[1]);
	life->time_to_die = ft_atol(argv[2]);
	life->time_to_eat = ft_atol(argv[3]);
	life->time_to_sleep = ft_atol(argv[4]);
	if (check_correct_imput(life->nbr_of_philos, life->time_to_die,
			life->time_to_eat, life->time_to_sleep))
		return (1);
	if (!argv[5])
		life->amount_of_meals = -1;
	else
		life->amount_of_meals = ft_atol(argv[5]);
	return (0);
}
