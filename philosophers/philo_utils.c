/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:31:37 by iarefeva          #+#    #+#             */
/*   Updated: 2025/01/20 15:25:09 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *error)
{
	printf("[ERROR]. %s\n", error);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	action_print(t_philo *philo, t_philo_life *life, t_phylo_status status)
{
	long	time;

	time = ft_timestamp(life);
	pthread_mutex_lock(&life->print_mutex);
	if (!life_ended(life) && status == EATING)
		printf("%ld %ld is eating\n", time, philo->philo_id + 1);
	else if (!life_ended(life) && status == THINKING)
		printf("%ld %ld is thinking\n", time, philo->philo_id + 1);
	else if (!life_ended(life) && status == SLEEPING)
		printf("%ld %ld is sleeping\n", time, philo->philo_id + 1);
	else if (!life_ended(life) && (status == TAKE_FIRST_FORK
			|| status == TAKE_SECOND_FORK))
		printf("%ld %ld has taken a fork\n", time, philo->philo_id + 1);
	else if (!life_ended(life) && status == DIED)
		printf("%ld %ld died\n", time, philo->philo_id + 1);
	pthread_mutex_unlock(&life->print_mutex);
}

void	precise_usleep(long usec, t_philo_life *life)
{
	long	start_time;
	long	current_time;
	long	remain;

	start_time = get_time_in_ms() * 1000;
	while (get_time_in_ms() * 1000 - start_time < usec)
	{
		if (life_ended(life))
			break ;
		current_time = get_time_in_ms() * 1000 - start_time;
		remain = usec - current_time;
		if (remain > 1000)
			usleep(remain / 2);
		else
		{
			while (get_time_in_ms() * 1000 - start_time < usec)
				;
		}
	}
}

int	safe_thr_hand(pthread_t *t, void *(*foo)(void *), void *d, t_opcode c)
{
	if (CREATE == c)
	{
		if (pthread_create(t, NULL, foo, d))
			return (2);
	}
	else if (JOIN == c)
	{
		if (pthread_join(*t, NULL))
			return (2);
	}
	return (0);
}
