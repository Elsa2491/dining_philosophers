/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:29 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/25 21:08:46 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h>

typedef struct s_philo
{
	struct s_table		*table;
	pthread_mutex_t		*right_f;
	pthread_mutex_t		*left_f;
	pthread_mutex_t		*meal_eaten;
	int					nb_of_meals_eaten;
	size_t				last_meal;
}	t_philo;

typedef struct s_table
{
	size_t		program_start;
	t_philo		*philo_tab;
	pthread_mutex_t	*fork_tab;
	pthread_mutex_t	message;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	pthread_mutex_t	main_thread;
	pthread_t	*thread_id;
	int			philo_nb;
	int			fork_nb;
	size_t		time_before_dying;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_think;
	int			nb_of_meals;
	int			is_dead;
}	t_table;

#endif
