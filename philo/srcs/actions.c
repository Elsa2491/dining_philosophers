/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/19 16:22:58 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_take_forks(t_table *table, t_philo *philo, int id)
{
	size_t	timestamps;

	timestamps = ft_get_current_time() - table->program_start;
/*(
	if (table->philo_nb == 1)
	{
		dprintf(2, "je pazse ici\n");
		ft_print_message("has taken a fork", table, id);
		if (table->time_before_dying < table->time_to_eat)
			ft_usleep(table->time_before_dying);
		printf("%zu %d is died\n", timestamps, id);
	//	pthread_mutex_unlock(philo->left_f);
	// //	free(philo->left_f);
	// 	free(&table->fork_tab[0]);
		
	// 	free(table->philo_tab);
		//free(&(table->thread_id));
		ft_free_tab(table);
//		pthread_mutex_destroy((table->thread_id));
		free(table->thread_id);
		free(table->fork_tab);
		free(table->philo_tab);

		exit (1);
	}
*/
	if (pthread_mutex_lock(philo->left_f) == 0)
		ft_print_message("has taken a fork", table, id);
	else
		printf("Error: left fork lock failed\n");

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
	pthread_mutex_lock(&table->meal);
	philo->last_meal = ft_get_current_time();
	pthread_mutex_unlock(&table->meal);
	ft_usleep(philo->table->time_to_eat);
	ft_drop_forks(philo);
}

void	ft_sleep(t_table *table, t_philo *philo, int id)
{
	ft_print_message("is sleeping", table, id);
	ft_usleep(philo->table->time_to_sleep);
}

void	ft_think(t_table *table, int id)
{
	ft_print_message("is thinking", table, id);
}
