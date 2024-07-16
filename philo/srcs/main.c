/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/16 14:19:23 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// dead_loop
int	ft_no_one_died(t_table *table)
{
//	dprintf(2, "\t->%s\n", __func__);
	int	i;

	i = 0;
	pthread_mutex_lock(&table->dead);	
	while (i < table->philo_nb)
	{
		if (table->philo_tab[i]->table->is_dead == 1)
		{
			pthread_mutex_unlock(&table->dead);
			return (1);
		}
		i += 1;
	}
	pthread_mutex_unlock(&table->dead);
	return (0);
}

void	*ft_routine(void *args)
{
	t_philo **philo_ptr;
	t_philo	*philo;
	t_table	*table;
	int	id;

	philo_ptr = (t_philo **)args;
	philo = *philo_ptr;
	table = philo->table;
	id = philo_ptr - table->philo_tab + 1;
//	if (id % 2 == 0)
//		usleep(1);
	while (!ft_no_one_died(table))
	{
		ft_eat(table, philo_ptr, id);
		ft_sleep(table, philo_ptr, id);
		ft_think(table, philo_ptr, id);
	}
	return (philo);
}

void	ft_handle_one_philo(t_table *table)
{
	if (table->time_before_dying < table->time_to_eat)
	{
		ft_usleep(table->time_before_dying);
		exit (1);
	}
}

void	ft_destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
		pthread_mutex_destroy(table->fork_tab[i++]);
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_check_params(argc, argv);
	memset(&table, 0, sizeof(t_table));
	ft_init_table(&table, argv);
	ft_init_forks(&table);
	ft_init_philos(&table);
	if (table.philo_nb == 1)
		ft_handle_one_philo(&table);
	ft_init_threads(&table);
	ft_destroy_mutex(&table);
	pthread_mutex_destroy(&table.message);
	pthread_mutex_destroy(&table.dead);
	pthread_mutex_destroy(&table.meal);
//	pthread_mutex_destroy(&table.dead_lock);
	ft_free_tab(&table);
}
