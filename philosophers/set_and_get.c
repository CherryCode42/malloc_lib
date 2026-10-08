/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:42:39 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/18 20:14:19 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mut *mut, bool *dest, bool value)
{
	pthread_mutex_lock(mut);
	*dest = value;
	pthread_mutex_unlock(mut);
}

bool	get_bool(t_mut *mut, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mut);
	ret = *value;
	pthread_mutex_unlock(mut);
	return (ret);
}

void	set_long(t_mut *mut, long *dest, long value)
{
	pthread_mutex_lock(mut);
	*dest = value;
	pthread_mutex_unlock(mut);
}

long	get_long(t_mut *mut, long *value)
{
	long	ret;

	pthread_mutex_lock(mut);
	ret = *value;
	pthread_mutex_unlock(mut);
	return (ret);
}

bool	life_ended(t_philo_life *life)
{
	return (get_bool(&(life->table_mutex), &life->end_of_dinner));
}
