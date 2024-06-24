/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:29 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/24 20:02:39 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h>

typedef enum e_all_states
{
	EAT = 1,
	SLEEP,
	THINK,
	DEAD,
}	t_all_states;

typedef struct s_time
{
	time_t	sec;
	long	nano_sec;
}	t_time;

typedef struct s_state
{
	t_all_states	type;
	//	pthread_mutex_t	state_mutex;
	struct s_state	*next;
	struct s_state	*prev;
}	t_state;

typedef struct s_fork
{
	int	i;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t	philo;
	t_state		*state;
	t_fork		*right_f;
	t_fork		*left_f;
	int		i;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_data
{
	t_philo		*philo;
	t_state		*state;
	t_fork		*right_f;
	t_fork		*left_f;
	int		philo_nb;
	long		time_to_eat;
	long		time_to_think;
	long		time_to_sleep;
	int		is_die;
	//pthread_mutex_t	philo_mutex;
	pthread_mutex_t	data_mutex;
}	t_data;

#endif
