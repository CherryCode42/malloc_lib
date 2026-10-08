/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:48:08 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/18 20:11:18 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_life(t_philo_life *life)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < life->nbr_of_philos)
	{
		philo = life->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&life->table_mutex);
	pthread_mutex_destroy(&life->print_mutex);
	free(life->philos);
	free(life->forks);
	free(life);
}
