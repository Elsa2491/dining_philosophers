/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/25 20:00:13 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// check if one should die
int	ft_is_dead(t_table *table, t_philo *philo, size_t dead)
{
	pthread_mutex_lock(&table->meal);
	dead -= philo->last_meal;
	if (dead > table->time_before_dying)
	{
		pthread_mutex_unlock(&table->meal);
		return (1);
	}
	pthread_mutex_unlock(&table->meal);
	return (0);
}

// edit dead value
int	ft_check_if_dead(t_table *table, t_philo *philo)
{
	int		i;
	size_t	dead;

	i = 0;
	dead = ft_get_current_time();
	while (i < table->philo_nb)
	{
		if (ft_is_dead(table, philo, dead))
		{
			pthread_mutex_lock(&table->dead);
			table->is_dead = 1;
			pthread_mutex_unlock(&table->dead);
			pthread_mutex_lock(&table->message);
			printf("%zu %d died\n", dead - table->program_start, i + 1);
			pthread_mutex_unlock(&table->message);
			return (1);
		}
		i += 1;
	}
	return (0);
}

int     ft_is_meal_max_reached(t_table *table)
{
	int     i;
	int	count;

	i = 0;
	count = 0;
	pthread_mutex_lock(&table->meal);
	while (i < table->philo_nb)
	{
		if (table->philo_tab[i].nb_of_meals_eaten == table->nb_of_meals)
			count += 1;
		i += 1;
	}
	pthread_mutex_unlock(&table->meal);
	if (count == table->philo_nb)
	{
		pthread_mutex_lock(&table->dead);
		table->is_dead = 1;
		pthread_mutex_unlock(&table->dead);
		return (1);
	}
	return (0);
}


void	ft_monitoring(t_table *table, t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (ft_check_if_dead(table, philo) || ft_is_meal_max_reached(table))
			return ;
	}
}
