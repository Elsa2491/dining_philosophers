/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/19 16:57:19 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	ft_check_if_dead(t_table *table, t_philo *philo, int id)
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
			printf("%zu %d died\n", dead - table->program_start, id);
			pthread_mutex_unlock(&table->message);
			return (1);
		}
		i += 1;
	}
	return (0);
}

int     ft_is_meal_max_reached(t_table *table, t_philo *philo, int id)
{
        (void)philo;
        (void)id;
        int     i;
//        int     finish;

      i = 0;
//        finish = 0;
        if (table->nb_of_meals == 1)
	{
		dprintf(2, "je passe la\n");
                exit (1);
	}
/*
        while (i < table->philo_nb)
        {
                if (table->philo_tab[i].nb_of_meals_eaten <= table->nb_of_meals)
                        table->philo_tab[i].nb_of_meals_eaten += 1;
                i += 1;
        }
        if (table->philo_tab[0].nb_of_meals_eaten == table->nb_of_meals)
                return (1);
        return (0);
*/
        return (0);
}


void	ft_monitoring(t_table *table, t_philo *philo)
{
	int	id;

	id = philo - table->philo_tab + 1;
	while (1)
		if (ft_check_if_dead(table, philo, id)) // || ft_is_meal_max_reached(table, philo, id))
			break ;
}
