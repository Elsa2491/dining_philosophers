/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/17 20:13:50 by eltouma          ###   ########.fr       */
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

int	ft_check_if_dead(t_table *table, t_philo **philo)
{
	int		i;
	size_t	dead;

	i = 0;
//	pthread_mutex_lock(&table->dead);
	dead = ft_get_current_time();
//	dprintf(2, "dead = %zu\n", dead);
	while (i < table->philo_nb)
	{
		if (ft_is_dead(table, &philo[i], dead))
		{
			pthread_mutex_lock(&table->dead);
			table->is_dead = 1;
			pthread_mutex_unlock(&table->dead);
			dprintf(2, "JE SUIS MORT\n");
			return (1);
		}
		i += 1;
	}
//		pthread_mutex_unlock(&table->dead);
	return (0);
}

void	ft_monitoring(t_table *table, t_philo **philo)
{
	while (1)
		if (ft_check_if_dead(table, philo) == 1)
			break;
}
