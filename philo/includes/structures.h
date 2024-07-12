/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:29 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/02 12:52:21 by eltouma          ###   ########.fr       */
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

typedef struct s_philo
{
	struct s_table		*table;
	t_state		*state;
	pthread_mutex_t		*right_f;
	pthread_mutex_t		*left_f;
}	t_philo;

typedef struct s_table
{
	t_philo		**philo_tab;
	pthread_mutex_t	**fork_tab;
	pthread_mutex_t	message;
	pthread_t	*thread_id;
	int		philo_nb;
	int		fork_nb;
	size_t		time_before_dying;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_think;
	size_t		is_dead;
	size_t		program_start;
	pthread_mutex_t	**table_mutex;
}	t_table;

#endif
