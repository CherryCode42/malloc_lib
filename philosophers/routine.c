/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:52:54 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/20 15:25:29 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *data)
{
	t_philo			*philo;
	t_philo_life	*life;

	philo = (t_philo *)data;
	life = philo->life_rules;
	wait_all_threads(life);
	set_long(&philo->philo_mutex, &philo->last_meal_time, ft_timestamp(life));
	increase_long(&life->table_mutex, &life->threads_running_nmbr);
	action_print(philo, life, TAKE_FIRST_FORK);
	while (!life_ended(life))
		usleep(200);
	return (NULL);
}

static void	thinking_proc(t_philo *philo)
{
	t_philo_life	*life;

	life = philo->life_rules;
	action_print(philo, life, THINKING);
	usleep(100);
}

static void	eating_proc(t_philo *philo)
{
	t_philo_life	*life;

	life = philo->life_rules;
	pthread_mutex_lock(&philo->first_fork->fork);
	action_print(philo, philo->life_rules, TAKE_FIRST_FORK);
	pthread_mutex_lock(&philo->second_fork->fork);
	action_print(philo, philo->life_rules, TAKE_SECOND_FORK);
	set_long(&philo->philo_mutex, &philo->last_meal_time, ft_timestamp(life));
	philo->nb_of_meal++;
	action_print(philo, philo->life_rules, EATING);
	precise_usleep(philo->life_rules->time_to_eat * 1000, philo->life_rules);
	if (philo->life_rules->amount_of_meals > 0
		&& philo->nb_of_meal == philo->life_rules->amount_of_meals)
		set_bool(&(philo->philo_mutex), &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*routine(void *data)
{
	t_philo			*philo;
	t_philo_life	*life;

	philo = (t_philo *)data;
	life = philo->life_rules;
	increase_long(&life->table_mutex, &life->threads_running_nmbr);
	wait_all_threads(life);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_in_ms());
	if (philo->philo_id % 2 == 0)
	{
		action_print(philo, life, THINKING);
		precise_usleep(life->time_to_eat * 1000, life);
	}
	while (!life_ended(life))
	{
		if (philo->full)
			break ;
		eating_proc(philo);
		action_print(philo, life, SLEEPING);
		precise_usleep(life->time_to_sleep * 1000, life);
		thinking_proc(philo);
	}
	return (NULL);
}
