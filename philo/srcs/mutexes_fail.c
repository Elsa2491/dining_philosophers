/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_fail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:47:51 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/30 18:49:52 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_check_unlock_dead(t_table *table)
{
	if (pthread_mutex_unlock(&table->dead) != 0)
		printf("Error: dead mutex unlock failed\n");
}

void	ft_check_unlock_meal(t_table *table)
{
	if (pthread_mutex_unlock(&table->meal) != 0)
		printf("Error: meal mutex unlock failed\n");
}

void	ft_check_unlock_main_thread(t_table *table)
{
	if (pthread_mutex_unlock(&table->main_thread) != 0)
		printf("Error: main thread mutex unlock failed\n");
}
