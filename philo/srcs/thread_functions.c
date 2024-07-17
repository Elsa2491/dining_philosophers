/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/17 20:30:15 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_init_mutexes(t_table *table)
{
	pthread_mutex_init(&table->message, NULL);
	pthread_mutex_init(&table->dead, NULL);
	pthread_mutex_init(&table->meal, NULL);
}

static void	ft_join_threads(t_table *table)
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
	// Mutex pour attendre la creation des threads
	ft_init_mutexes(table);
	while (i < table->philo_nb)
	{
		if (pthread_create(&(table->thread_id[i]), NULL, &ft_routine, &(table->philo_tab[i])) != 0)
		{
			dprintf(2, "Attention tout le monde, je fail %d!\n", i);
		// Attention, si le thread 3 fail, il faut join les threads crees et tout arreter
			return ;
		}
		i += 1;
	}
	// init le temps de depart ici
// table->program_start = ft_get_current_time();
	// Unlock mutex 
	ft_monitoring(table, table->philo_tab);
	ft_join_threads(table);
}
