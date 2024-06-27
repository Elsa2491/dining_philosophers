/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/27 14:51:11 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	ft_init_table(t_table *table, char **argv)
{
	table->philo_nb = ft_atoi(argv[1]);
//	table->fork_nb = ft_atoi(argv[1]);
	table->time_before_dying = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	dprintf(2, " Philo num:\t\t%d\n", table->philo_nb);
	dprintf(2, " Fork num:\t\t%d\n", table->philo_nb);
	dprintf(2, " Time before dying:\t%d\n", table->time_before_dying);
	dprintf(2, " Time to eat:\t\t%d\n", table->time_to_eat);
	dprintf(2, " Time to sleep:\t\t%d\n", table->time_to_sleep);
}

void	ft_init_philos_and_forks(t_table *table)
{
	int	i;

	i = 0;
	table->philo_tab = (t_philo **)malloc(sizeof(t_philo *) * table->philo_nb);
	if (!table->philo_tab)
		return ;
	table->fork_tab = (t_fork **)malloc(sizeof(t_fork *) * table->philo_nb);
	if (!table->fork_tab)
		return ;
	while (i < table->philo_nb)
	{
		table->philo_tab[i] = (t_philo *)malloc(sizeof(t_philo));
		// check if malloc fail
		// if (!table->philo_tab[i])
		//	ft_free_tab(table, i);
		//table->fork_tab[i++] = (t_fork *)malloc(sizeof(t_fork));
		table->fork_tab[i] = (t_fork *)malloc(sizeof(t_fork));
		// check if malloc fail
//		dprintf(2, "table->philo_tab[%d]\t-> %ld\n", i, (long)table->philo_tab[i]);
//		dprintf(2, "table->fork_tab[%d]\t-> %ld\n", i, (long)table->fork_tab[i]);
		dprintf(2, "table->philo_tab\t-> %d\n", i);
		dprintf(2, "table->fork_tab\t\t-> %d\n", i);
		i += 1;
	}
}
