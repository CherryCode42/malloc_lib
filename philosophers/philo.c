/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:26:58 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/18 20:35:17 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_life	*life;

	if (argc != 5 && argc != 6)
	{
		print_error("Wrong imput! It should be ./philo 2 800 200 200 [3]");
		return (0);
	}
	else
	{
		life = malloc(sizeof(t_philo_life));
		if (!life)
			return (1);
		if (life_parse(argv, life))
		{
			free(life);
			return (0);
		}
		life_init(life);
		routine_life(life);
		clean_life(life);
	}
	return (0);
}
