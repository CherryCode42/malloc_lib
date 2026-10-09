/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarefeva <iarefeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:37:43 by iarefeva          #+#    #+#             */
/*   Updated: 2026/10/08 10:27:06 by iarefeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include "../inc/malloc.h"

typedef pthread_mutex_t	t_mut;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}	t_opcode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_phylo_status;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t			thread_id;
	long				philo_id;
	long				nb_of_meal;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_mut				philo_mutex;
	bool				full;
	long				last_meal_time;
	struct s_philo_life	*life_rules;
}	t_philo;

typedef struct s_philo_life
{
	long		nbr_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		amount_of_meals;
	long		start_time;
	long		threads_running_nmbr;
	bool		all_ready_to_start;
	bool		end_of_dinner;
	t_mut		table_mutex;
	t_mut		print_mutex;
	t_philo		*philos;
	t_fork		*forks;
	pthread_t	doctor;
}	t_philo_life;

//utils
void	print_error(char *error);
int		ft_strlen(const char *str);
void	action_print(t_philo *philo, t_philo_life *life, t_phylo_status status);
void	precise_usleep(long usec, t_philo_life *life);

//process
int		life_parse(char	**argv, t_philo_life *life);
int		life_init(t_philo_life *life);
int		routine_life(t_philo_life	*life);
void	clean_life(t_philo_life *life);
void	*one_philo(void *data);
void	*routine(void *data);

//time
long	get_time_in_ms(void);
long	ft_timestamp(t_philo_life *life);

//set and get
void	set_bool(t_mut *mut, bool *dest, bool value);
bool	get_bool(t_mut *mut, bool *value);
void	set_long(t_mut *mut, long *dest, long value);
long	get_long(t_mut *mut, long *value);
bool	life_ended(t_philo_life *life);

//synchronisation
void	wait_all_threads(t_philo_life *life);
void	increase_long(t_mut *mut, long *value);
bool	all_threads_running(t_mut *mut, long *threads, long philo_nbr);
void	*check_philos(void	*data);

//safe func
int		safe_thr_hand(pthread_t *thread,
			void *(*foo)(void *), void *data, t_opcode opcode);

#endif