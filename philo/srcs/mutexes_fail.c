/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_fail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:47:51 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/31 11:47:27 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_handle_mutex_for_death(t_table *table)
{
	if (pthread_mutex_lock(&table->dead) == 0)
		table->is_dead = 1;
	else
		printf("Error: dead mutex lock failed\n");
	if (pthread_mutex_unlock(&table->dead) != 0)
		printf("Error: dead mutex unlock failed\n");
}

void	ft_handle_mutexes_ft_eat(t_table *table, t_philo *philo)
{
	if (pthread_mutex_lock(&table->meal) == 0)
	{
		philo->last_meal = ft_get_current_time();
/*
	else
		printf("Error: meal mutex lock failed\n");
	ft_check_unlock_meal(table);
	if (pthread_mutex_lock(&table->meal) == 0)
*/
		philo->nb_of_meals_eaten += 1;
	}
	else
		printf("Error: meal mutex lock failed\n");
	ft_check_unlock_meal(table);

}

void	ft_check_mutex_message(t_table *table, size_t dead, int i)
{
	if (pthread_mutex_lock(&table->message) == 0)
	{
		dead = ft_get_current_time();
		printf("%zu %d died\n", dead - table->program_start, i + 1);
	}
	else
		printf("Error: message mutex lock failed\n");
	if (pthread_mutex_unlock(&table->message) != 0)
		printf("Error: message mutex unlock failed\n");
}

void	ft_check_unlock_main_thread(t_table *table)
{
	if (pthread_mutex_unlock(&table->main_thread) != 0)
		printf("Error: main thread mutex unlock failed\n");
}

void	ft_check_unlock_meal(t_table *table)
{
	if (pthread_mutex_unlock(&table->meal) != 0)
		printf("Error: meal mutex unlock failed\n");
}

