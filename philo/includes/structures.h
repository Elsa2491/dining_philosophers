/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:29 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/16 15:29:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h>

/*
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

*/

typedef struct s_philo
{
	struct s_table		*table;
//	t_state		*state;
	pthread_mutex_t		*right_f;
	pthread_mutex_t		*left_f;
	size_t		last_meal;
	int		nb_of_meals_eaten;
//	pthread_mutex_t		*message;
//	pthread_mutex_t		*dead;
}	t_philo;

typedef struct s_table
{
	t_philo		**philo_tab;
	pthread_mutex_t	**fork_tab;
	pthread_mutex_t	message;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	pthread_t	*thread_id;
//	pthread_t	monitoring;
	int		philo_nb;
	int		fork_nb;
	size_t		time_before_dying;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_think;
	int		nb_of_meals;

	//size_t		last_meal;
	//int		is_eating;
	//int		nb_of_meals_eaten;
	int		is_dead;
	size_t		program_start;
	pthread_mutex_t	**mutex_tab;
}	t_table;

#endif
