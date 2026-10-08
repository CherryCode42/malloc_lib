/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:36:24 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/20 15:11:16 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long			elapsed;
	long			time_to_die;
	t_philo_life	*life;

	life = philo->life_rules;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = ft_timestamp(life) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = get_long(&life->table_mutex, &life->time_to_die);
	if (elapsed > time_to_die)
		return (true);
	else
		return (false);
}

void	*check_philos(void	*data)
{
	t_philo_life	*life;
	int				i;

	life = (t_philo_life *)data;
	while (!all_threads_running(&life->table_mutex, &life->threads_running_nmbr,
			life->nbr_of_philos))
			;
	precise_usleep(life->time_to_die * 1000, life);
	while (!life_ended(life))
	{
		i = 0;
		while (i < life->nbr_of_philos)
		{
			if (philo_died(life->philos + i))
			{
				action_print(life->philos + i, life, DIED);
				set_bool(&life->table_mutex, &life->end_of_dinner, true);
			}
			i++;
		}
	}
	return (NULL);
}
