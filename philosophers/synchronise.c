/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:59 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/18 20:16:53 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_philo_life *life)
{
	while (!get_bool(&life->table_mutex, &life->all_ready_to_start))
		;
}

bool	all_threads_running(t_mut *mut, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mut);
	if (*threads == philo_nbr)
		ret = true;
	pthread_mutex_unlock(mut);
	return (ret);
}

void	increase_long(t_mut *mut, long *value)
{
	pthread_mutex_lock(mut);
	(*value)++;
	pthread_mutex_unlock(mut);
}
