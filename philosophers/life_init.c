/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:16:36 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/20 15:17:08 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	create_philo(t_philo_life *life, t_fork *forks, int i)
{
	t_philo	philo;

	philo.philo_id = i;
	philo.nb_of_meal = 0;
	philo.full = false;
	pthread_mutex_init(&philo.philo_mutex, NULL);
	philo.first_fork = &forks[(i + 1) % life->nbr_of_philos];
	philo.second_fork = &forks[i];
	if (philo.philo_id % 2 == 0)
	{
		philo.first_fork = &forks[i];
		philo.second_fork = &forks[(i + 1) % life->nbr_of_philos];
	}
	philo.life_rules = life;
	return (philo);
}

static void	philo_init(t_philo_life *life)
{
	int	i;

	i = 0;
	while (i < life->nbr_of_philos)
	{
		life->philos[i] = create_philo(life, life->forks, i);
		i++;
	}
}

int	life_init(t_philo_life *life)
{
	int	i;

	i = 0;
	life->all_ready_to_start = false;
	life->end_of_dinner = false;
	life->threads_running_nmbr = 0;
	life->philos = malloc(sizeof(t_philo) * life->nbr_of_philos);
	if (!life->philos)
		return (1);
	pthread_mutex_init(&life->table_mutex, NULL);
	pthread_mutex_init(&life->print_mutex, NULL);
	life->forks = malloc(sizeof(t_fork) * life->nbr_of_philos);
	if (!life->forks)
		return (1);
	while (i < life->nbr_of_philos)
	{
		pthread_mutex_init(&life->forks[i].fork, NULL);
		life->forks[i].fork_id = i;
		i++;
	}
	philo_init(life);
	return (0);
}
