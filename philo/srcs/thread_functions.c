/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/24 21:12:05 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_init_mutexes(t_table *table)
{
	pthread_mutex_init(&table->message, NULL);
	pthread_mutex_init(&table->dead, NULL);
	pthread_mutex_init(&table->meal, NULL);
}

void	ft_destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
		pthread_mutex_destroy((&table->fork_tab[i++]));
	pthread_mutex_destroy(&table->message);
	pthread_mutex_destroy(&table->dead);
	pthread_mutex_destroy(&table->meal);
}

void	ft_join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_join(table->thread_id[i], NULL) != 0)
			return ;
		i += 1;
	}
}

void	ft_init_threads(t_table *table)
{
	int	i;

	i = 0;
	table->thread_id = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_nb);
	if (!table->thread_id)
		return ;
	ft_init_mutexes(table);
	pthread_mutex_init(&table->main_thread, NULL);
	pthread_mutex_lock(&table->main_thread);
	while (i < table->philo_nb)
	{
		if (pthread_create(&(table->thread_id[i]), NULL, &ft_routine,
				&(table->philo_tab[i])) != 0)
		{
			while (i > 0)
				pthread_join(table->thread_id[i--], NULL);
			free(table->thread_id);
			return ;
		}
		i += 1;
	}
	table->program_start = ft_get_current_time();
	pthread_mutex_unlock(&table->main_thread);
	ft_monitoring(table, table->philo_tab);
	ft_join_threads(table);
}
