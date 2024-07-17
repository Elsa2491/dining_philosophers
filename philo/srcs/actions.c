/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/17 17:27:17 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_take_forks(t_table *table, t_philo **philo, int id)
{
	if (pthread_mutex_lock((*philo)->left_f) == 0)
		ft_print_message("has taken a fork", table, id);
	else 
		printf("Error: left fork lock failed\n");
	if (table->philo_nb == 1)
	{
		if (table->time_before_dying < table->time_to_eat)
			ft_usleep(table->time_before_dying);
		else
			ft_usleep(table->time_to_eat);
		pthread_mutex_unlock((*philo)->left_f);
		exit (1);
	}
	if (pthread_mutex_lock((*philo)->right_f) == 0)
		ft_print_message("has taken a fork", table, id);
	else
		printf("Error: right fork lock failed\n");
}

void	ft_drop_forks(t_philo **philo)
{
	if (pthread_mutex_unlock((*philo)->right_f) != 0)
		printf("Error: right fork unlock failed\n");
	if (pthread_mutex_unlock((*philo)->left_f) != 0)
		printf("Error: right fork unlock failed\n");
}

void	ft_eat(t_table *table, t_philo **philo, int id)
{
	ft_take_forks(table, philo, id);
	ft_print_message("is eating", table, id);

	pthread_mutex_lock(&table->meal);
	(*philo)->last_meal = ft_get_current_time();
	pthread_mutex_unlock(&table->meal);

	ft_usleep((*philo)->table->time_to_eat);
	ft_drop_forks(philo);
}

void	ft_sleep(t_table *table, t_philo **philo, int id)
{
	ft_print_message("is sleeping", table, id);
	ft_usleep((*philo)->table->time_to_sleep);
}

void	ft_think(t_table *table, int id)
{
	ft_print_message("is thinking", table, id);
}
