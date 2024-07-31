/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/31 11:46:54 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_take_forks(t_table *table, t_philo *philo, int id)
{
	if (pthread_mutex_lock(philo->left_f) == 0)
		ft_print_message("has taken a fork", table, id);
	else
		printf("Error: left fork lock failed\n");
	if (table->philo_nb == 1)
	{
		ft_usleep(table, table->time_before_dying);
		if (pthread_mutex_unlock(philo->left_f) != 0)
			printf("Error: left fork unlock failed\n");
		ft_handle_mutex_for_death(table);
		return ;
	}
	if (pthread_mutex_lock(philo->right_f) == 0)
		ft_print_message("has taken a fork", table, id);
	else
		printf("Error: right fork lock failed\n");
}

void	ft_drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->right_f) != 0)
		printf("Error: right fork unlock failed\n");
	if (pthread_mutex_unlock(philo->left_f) != 0)
		printf("Error: left fork unlock failed\n");
}

void	ft_eat(t_table *table, t_philo *philo, int id)
{
	ft_take_forks(table, philo, id);
	ft_print_message("is eating", table, id);
	ft_handle_mutexes_ft_eat(table, philo);
	ft_usleep(table, philo->table->time_to_eat);
	if (table->philo_nb > 1)
		ft_drop_forks(philo);
}

void	ft_sleep(t_table *table, t_philo *philo, int id)
{
	ft_print_message("is sleeping", table, id);
	ft_usleep(table, philo->table->time_to_sleep);
}

void	ft_think(t_table *table, int id)
{
	ft_print_message("is thinking", table, id);
	if (table->time_to_eat > table->time_to_sleep)
		ft_usleep(table, table->time_to_eat - table->time_to_sleep + 5);
	else if (id & 1)
		ft_usleep(table, 5);
}
