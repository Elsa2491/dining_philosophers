/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/18 11:40:29 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_is_dead(t_table *table, t_philo **philo, size_t dead)
{
	pthread_mutex_lock(&table->meal);
	dead -= (*philo)->last_meal;
	if (dead > table->time_before_dying)
	{
		pthread_mutex_unlock(&table->meal);
		return (1);
	}
	pthread_mutex_unlock(&table->meal);
	return (0);
}

int	ft_check_if_dead(t_table *table, t_philo **philo, int id)
{
	int		i;
	size_t	dead;

	i = 0;
	dead = ft_get_current_time();
	while (i < table->philo_nb)
	{
		if (ft_is_dead(table, &philo[i], dead))
		{
			pthread_mutex_lock(&table->dead);
			table->is_dead = 1;
			pthread_mutex_unlock(&table->dead);
			pthread_mutex_lock(&table->message);
			printf("%zu %d is died\n", dead - table->program_start, id);
			pthread_mutex_unlock(&table->message);
			return (1);
		}
		i += 1;
	}
	return (0);
}

void	ft_monitoring(t_table *table, t_philo **philo)
{
	int	id;

	id = philo - table->philo_tab + 1;
	while (1)
		if (ft_check_if_dead(table, philo, id) == 1)
			break ;
}
