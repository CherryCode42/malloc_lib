/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_life_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:45:02 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/20 14:02:37 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_all_threads(t_philo_life *life)
{
	int	i;

	i = -1;
	while (++i < life->nbr_of_philos)
	{
		if (safe_thr_hand(&life->philos[i].thread_id, NULL, NULL, JOIN))
			return (2);
	}
	set_bool(&life->table_mutex, &life->end_of_dinner, true);
	if (safe_thr_hand(&life->doctor, NULL, NULL, JOIN))
		return (2);
	return (0);
}

static int	all_threads_create(t_philo_life *life)
{
	int	i;

	i = -1;
	while (++i < life->nbr_of_philos)
	{
		if (safe_thr_hand(&life->philos[i].thread_id,
				routine, &life->philos[i], CREATE))
			return (2);
	}
	return (0);
}

int	routine_life(t_philo_life	*life)
{
	if (life->amount_of_meals == 0)
		return (0);
	else if (life->nbr_of_philos == 1)
	{
		if (safe_thr_hand(&life->philos[0].thread_id, one_philo,
				&life->philos[0], CREATE))
			return (2);
	}
	else
		all_threads_create(life);
	life->start_time = get_time_in_ms();
	if (safe_thr_hand(&life->doctor, check_philos, life, CREATE))
		return (2);
	set_bool(&life->table_mutex, &life->all_ready_to_start, true);
	if (join_all_threads(life))
		return (2);
	return (0);
}
