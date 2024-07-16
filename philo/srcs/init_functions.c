/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/16 16:42:08 by eltouma          ###   ########.fr       */
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
	table->program_start = ft_get_current_time();
//	table->last_meal = ft_get_current_time();
	dprintf(2, " Philo num:\t\t%d\n", table->philo_nb);
	dprintf(2, " Fork num:\t\t%d\n", table->fork_nb);
	dprintf(2, " Time before dying:\t%zu\n", table->time_before_dying);
	dprintf(2, " Time to eat:\t\t%zu\n", table->time_to_eat);
	dprintf(2, " Time to sleep:\t\t%zu\n", table->time_to_sleep);
	dprintf(2, " Nb of meals:\t\t%d\n", table->nb_of_meals);
	dprintf(2, " Program start:\t\t%zu\n", table->program_start);
}

void	ft_init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->fork_tab = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * table->fork_nb);
	if (!table->fork_tab)
		return ;
	while (i < table->fork_nb)
	{
		table->fork_tab[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!table->fork_tab[i])
			return ;
		pthread_mutex_init(table->fork_tab[i], NULL);
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
		table->philo_tab[i]->table = table;
		table->philo_tab[i]->nb_of_meals_eaten = 0;
		table->philo_tab[i]->last_meal = ft_get_current_time();
		dprintf(2, " Last meal:\t\t%zu\n", table->philo_tab[i]->last_meal);
		table->philo_tab[i]->left_f = table->fork_tab[i];
		table->philo_tab[i]->right_f = table->fork_tab[(i + 1) % table->philo_nb];
//		table->philo_tab[i]->is_dead = 0; 
		if (i == table->philo_nb - 1)
		{
			table->philo_tab[i]->left_f = table->fork_tab[i];
//			dprintf(2, "philo %d a la fourchette %d comme fourchette gauche ", i, i);
			table->philo_tab[i]->right_f = table->fork_tab[0];
//			dprintf(2, "et la fourchette 0 comme fourchette droite\n");
		}
		else
		{
			table->philo_tab[i]->right_f = table->fork_tab[i];
//			dprintf(2, "philo %d a la fourchette %d comme fourchette droite ", i, i);
			table->philo_tab[i]->left_f = table->fork_tab[i + 1];
//			dprintf(2, "et la fourchette %d comme fourchette gauche\n", i + 1);
		}
		i += 1;
	}
}

int	ft_is_dead(t_table *table, t_philo **philo, size_t dead) //, size_t time_before_dying)
{
// mutex meal;
	
	pthread_mutex_lock(&table->meal);
	dead -= (*philo)->last_meal;
//	dprintf(2, "last_meal de chaque philo = %zu\n", (*philo)->last_meal);
	if (dead > table->time_before_dying) // && (*philo)->table->is_eating == 0)
	{

		pthread_mutex_unlock(&table->meal);
		dprintf(2, "\t\tOUI\n");
		return (1);
	}
	pthread_mutex_unlock(&table->meal);
	return (0);
}

int	ft_check_if_dead(t_table *table, t_philo **philo)
{
	int	i;
	size_t	dead;

	i = 0;
	pthread_mutex_lock(&table->dead);
	dead = ft_get_current_time(); // - table->time_before_dying;
//	dprintf(2, "dead = %zu\n", dead);
	while (i < table->philo_nb)
	{
		if (ft_is_dead(table, &philo[i], dead)) // , philo, table->time_before_dying))
		{
			table->is_dead = 1;
			pthread_mutex_unlock(&table->dead);
			dprintf(2, "JE SUIS MORT\n");
			return (1);
		}
		i += 1;
	}
		pthread_mutex_unlock(&table->dead);
	return (0);
}

void	ft_monitoring(t_table *table, t_philo **philo)
{
//	t_philo	**philo_ptr;
//	t_philo	*philo;
	//t_table	*table;
//	int	id;

//	philo_ptr = (t_philo **)args;
//	philo = *philo_ptr;
//	table = philo->table;
//	id = philo_ptr - table->philo_tab+ 1;
	while (1)
	{
		if (ft_check_if_dead(table, philo) == 1)
			break;
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
/* -----------------------------------------------------------------------------
	// Pourquoi j'ai fait ça ?
	while (i < table->philo_nb)
	{
		pthread_mutex_init(table->fork_tab[i], NULL);
		pthread_mutex_init(&table->message, NULL);
		pthread_mutex_init(&table->dead_lock, NULL);
		i += 1;
	}
	i = 0;
----------------------------------------------------------------------------- */
//	pthread_mutex_init(&table->message, NULL);
//	pthread_mutex_init(&table->philo_tab[i]->dead_lock, NULL);
//	if (pthread_create(&(table->monitoring), NULL, &ft_monitoring, &(table->philo_tab[i])) != 0)
//		dprintf(2, "Attention tout le monde, le monitoring fail !\n");
	pthread_mutex_init(&table->message, NULL);
	pthread_mutex_init(&table->dead, NULL);
	pthread_mutex_init(&table->meal, NULL);
	while (i < table->philo_nb)
	{
//		pthread_mutex_init(table->philo_tab[i]->dead_lock, NULL);
		if (pthread_create(&(table->thread_id[i]), NULL, &ft_routine, &(table->philo_tab[i])) != 0)
		{
			dprintf(2, "Attention tout le monde, je fail %d!\n", i);
		// Attention, si le thread 3 fail, il faut join les threads crees et tout arreter
			return ;
		}
		i += 1;	
	} 
	// Unlock mutex 
//	if (pthread_join(table->monitoring, NULL) != 0)
//		return ;
//	i = 0;
//	while (i < table->philo_nb)	
	ft_monitoring(table, table->philo_tab);
	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_join(table->thread_id[i], NULL) != 0)
			return ;
		i += 1;
	}
}
