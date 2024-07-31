/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/31 13:12:20 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_if_one_should_die(t_table *table, t_philo *philo, size_t dead)
{
	if (pthread_mutex_lock(&table->meal) != 0)
		printf("Error: meal mutex lock failed\n");
	dead -= philo->last_meal;
	if (table->philo_nb == 1)
	{
		ft_usleep(table, table->time_before_dying);
		ft_check_unlock_meal(table);
		return (1);
	}
	if (dead > table->time_before_dying)
	{
		ft_check_unlock_meal(table);
		return (1);
	}
	ft_check_unlock_meal(table);
	return (0);
}

int	ft_edit_dead_val(t_table *table, t_philo *philo)
{
	int		i;
	size_t	dead;

	i = 0;
	dead = ft_get_current_time();
	while (i < table->philo_nb)
	{
		if (ft_check_if_one_should_die(table, philo, dead))
		{
			ft_handle_mutex_for_death(table);
			ft_check_mutex_message(table, dead, i);
			return (1);
		}
		i += 1;
	}
	return (0);
}

int	ft_is_meal_max_reached(t_table *table)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (pthread_mutex_lock(&table->meal) != 0)
		printf("Error: meal mutex lock failed\n");
	while (i < table->philo_nb)
	{
		if (table->philo_tab[i].nb_of_meals_eaten == table->nb_of_meals)
			count += 1;
		i += 1;
	}
	ft_check_unlock_meal(table);
	if (count == table->philo_nb)
	{
		ft_handle_mutex_for_death(table);
		return (1);
	}
	return (0);
}

void	ft_monitoring(t_table *table, t_philo *philo)
{
	while (1)
	{
		usleep(100);
		if (ft_edit_dead_val(table, philo) || ft_is_meal_max_reached(table))
			return ;
	}
}
