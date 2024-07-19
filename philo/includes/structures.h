/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:29 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/19 17:14:19 by eltouma          ###   ########.fr       */
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
	size_t		last_meal;
	int			nb_of_meals_eaten;
	// int		id;
//	pthread_mutex_t		*message;
//	pthread_mutex_t		*dead;
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
	pthread_t	one_philo;
	int			philo_nb;
	int			fork_nb;
	size_t		time_before_dying;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_think;
	int			nb_of_meals;
	//size_t		last_meal;
	//int		is_eating;
	//int		nb_of_meals_eaten;
	int			is_dead;
}	t_table;

#endif
