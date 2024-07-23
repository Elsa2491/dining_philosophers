/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/23 22:01:20 by eltouma          ###   ########.fr       */
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
	pthread_mutex_lock(&table->main_thread);
	pthread_mutex_unlock(&table->main_thread);
	//if (!(philo_ptr->id & 1))
/*
	3 800 300 300
	on fait un decalage de 100 sur p2
*/
//	if (!(id & 1)) 
	if (id % 2 == 0)
		usleep(1000);
	if (id == table->philo_nb)
		ft_usleep(table, table->time_to_eat);
	while (!ft_no_one_died(table))
	{
		ft_eat(table, philo_ptr, id);
		ft_sleep(table, philo_ptr, id);
		ft_think(table, id);
		if (table->philo_nb & 1)
			usleep(100);
	}
	//dprintf(2, "fin de routine %d\n", id);
	return (philo_ptr);
}

void	*ft_handle_one_philo(void *args)
{
	t_philo	*philo_ptr;
	t_table	*table;
	int		id;

	philo_ptr = (t_philo *)args;
	table = philo_ptr->table;
	id = philo_ptr - table->philo_tab + 1;
	dprintf(2, "NIQUE TA MERE %d\n", id);
	return (philo_ptr);
}

void	ft_is_only_one_philo(t_table *table)
{
	if (pthread_create(&(table->one_philo), NULL, &ft_handle_one_philo, &(table->one_philo)) != 0)
		dprintf(2, "je fail sa mere\n");
	dprintf(2, "NIQUE TA PUTAIN DE MERE\n");
	exit (1);
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
		ft_is_only_one_philo(&table);
	ft_init_threads(&table);
//	ft_join_threads(&table);
	ft_destroy_mutexes(&table);
	pthread_mutex_destroy(&table.message);
	pthread_mutex_destroy(&table.dead);
	pthread_mutex_destroy(&table.meal);
	ft_free_tab(&table);
}
