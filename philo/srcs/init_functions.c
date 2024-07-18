/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/18 14:36:12 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_table(t_table *table, char **argv)
{
	table->philo_nb = ft_atoi(argv[1]);
	table->fork_nb = table->philo_nb;
	table->time_before_dying = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->nb_of_meals = ft_atoi(argv[5]);
	else
		table->nb_of_meals = -1;
}

void	ft_init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->fork_tab = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->fork_nb);
	if (!table->fork_tab)
		return ;
	while (i < table->fork_nb)
		pthread_mutex_init(&table->fork_tab[i++], NULL);
}

void	ft_init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo_tab = (t_philo *)malloc(sizeof(t_philo) * table->philo_nb);
	if (!table->philo_tab)
		return ;
	while (i < table->philo_nb)
	{
		table->philo_tab[i].table = table;
		table->philo_tab[i].nb_of_meals_eaten = 0;
		table->philo_tab[i].last_meal = ft_get_current_time();
		table->philo_tab[i].left_f = &(table->fork_tab[i]);
		table->philo_tab[i].right_f = &(table->fork_tab[(i + 1) % table->philo_nb]);
		if (i == table->philo_nb - 1)
		{
			table->philo_tab[i].left_f = &(table->fork_tab[i]);
			table->philo_tab[i].right_f = &(table->fork_tab[0]);
		}
		else
		{
			table->philo_tab[i].right_f = &(table->fork_tab[i]);
			table->philo_tab[i].left_f = &(table->fork_tab[i + 1]);
		}
		i += 1;
	}
}
