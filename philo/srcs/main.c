/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/31 13:12:04 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_no_one_died(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->dead);
	while (i < table->philo_nb)
	{
		if (table->philo_tab[i].table->is_dead == 1)
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
	t_philo	*philo_ptr;
	t_table	*table;
	int		id;

	philo_ptr = (t_philo *)args;
	table = philo_ptr->table;
	id = philo_ptr - table->philo_tab + 1;
	if (pthread_mutex_lock(&table->main_thread) != 0)
		printf("Error: main thread mutex lock failed\n");
	ft_check_unlock_main_thread(table);
	if (!(id & 1))
		usleep(1000);
	if (table->philo_nb & 1 && id == table->philo_nb && table->philo_nb > 1)
		ft_usleep(table, table->time_to_eat - 100);
	while (!ft_no_one_died(table))
	{
		ft_eat(table, philo_ptr, id);
		ft_sleep(table, philo_ptr, id);
		ft_think(table, id);
	}
	return (philo_ptr);
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_check_params(argc, argv);
	memset(&table, 0, sizeof(t_table));
	ft_init_table(&table, argv);
	ft_init_forks(&table);
	ft_init_philos(&table);
	ft_init_threads(&table);
	ft_destroy_mutexes(&table);
	ft_free_tab(&table);
}
