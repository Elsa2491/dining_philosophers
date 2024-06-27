/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/27 21:06:19 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	ft_init_table(t_table *table, char **argv)
{
	table->philo_nb = ft_atoi(argv[1]);
	table->fork_nb = ft_atoi(argv[1]);
	table->time_before_dying = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	dprintf(2, " Philo num:\t\t%d\n", table->philo_nb);
	dprintf(2, " Fork num:\t\t%d\n", table->philo_nb);
	dprintf(2, " Time before dying:\t%d\n", table->time_before_dying);
	dprintf(2, " Time to eat:\t\t%d\n", table->time_to_eat);
	dprintf(2, " Time to sleep:\t\t%d\n", table->time_to_sleep);
}

void	ft_init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->fork_tab = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * table->philo_nb);
	if (!table->fork_tab)
		return ;
	while (i < table->philo_nb)
	{
		table->fork_tab[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		// check if malloc fail
		dprintf(2, "table->fork_tab\t\t-> %d\n", i);
		i += 1;
	}
}

// INIT STATE
void	ft_init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo_tab = (t_philo **)malloc(sizeof(t_philo *) * table->philo_nb);
	if (!table->philo_tab)
		return ;
	while (i < table->philo_nb)
	{
		table->philo_tab[i] = (t_philo *)malloc(sizeof(t_philo));
		// check if malloc fail
		// if (!table->philo_tab[i])
		//	ft_free_tab(table, i);
		if (i == table->philo_nb - 1)
		{
			table->philo_tab[i]->left_f = table->fork_tab[i];
			dprintf(2, "philo n %d a la fourchette %d comme fourchette gauche ", i, i);
			table->philo_tab[i]->right_f = table->fork_tab[0];
			dprintf(2, "et la fourchette 0 comme fourchette droite\n");
		}
		else
		{
			table->philo_tab[i]->right_f = table->fork_tab[i];
			dprintf(2, "philo n %d a la fourchette %d comme fourchette droite ", i, i);
			table->philo_tab[i]->left_f = table->fork_tab[i + 1];
			dprintf(2, "et la fourchette %d comme fourchette gauche\n", i + 1);
		}
		dprintf(2, "table->philo_tab\t-> %d\n", i);
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
	while (i < table->philo_nb)
	{
		pthread_mutex_init(table->fork_tab[i], NULL);
		i += 1;
	}
	i = 0;
	while (i < table->philo_nb)
	{
		dprintf(2, "\tcoucou\n");
		if (pthread_create(&(table->thread_id[i]), NULL, &ft_routine, &(table->philo_tab[i])) != 0)
		{
			dprintf(2, "Attention tout le monde, je fail !\n");
		// Attention, si le thread 3 fail, il faut join les threads crees et tout arreter
			return ;
		}
		i += 1;	
	} 
	// Unlock mutex 
	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_join(table->thread_id[i], NULL) != 0)
			return ;
		i += 1;
	}
}
