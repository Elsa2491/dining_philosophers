/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/02 19:00:11 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_message(char *str, t_table *table, int id);

void	ft_take_forks(t_table *table, t_philo **philo, int id)
{
	if (pthread_mutex_lock((*philo)->left_f) == 0)
//		printf("%zu %d has taken a fork (right)\n", ft_usleep((*philo)->table->time_to_sleep), id);
		ft_print_message("has taken a fork", table, id);
	else // si la fourchette est occupee, je ne rentre pas dans le else parce que pthread ne retourne rien dans ce cas la, donc je reste coincee sur cette meme ligne
		printf("error\n");
	if (pthread_mutex_lock((*philo)->right_f) == 0)
		printf("%zu %d has taken a fork (right)\n", ft_usleep((*philo)->table->time_to_sleep), id);
//		printf("%d has taken a fork (left) \n", id);
	else
		printf("error\n");
}

void	ft_drop_forks(t_philo **philo, int id)
{
	if (pthread_mutex_unlock((*philo)->right_f) == 0)
		printf("%d right fork lock \n", id);
	if (pthread_mutex_unlock((*philo)->left_f) == 0)
		printf("%d left fork lock \n", id);
}

void	ft_print_message(char *str, t_table *table, int id)
{
	pthread_mutex_lock(&table->message);
	size_t	time = ft_get_current_time() - table->program_start;
	dprintf(2, "\t\t-> get_current_time in %s = %zu\n", __func__, ft_get_current_time());
	dprintf(2, "\t\t-> table->program_start %zu\n", table->program_start);
	dprintf(2, "\t\t-> time %zu\n", time);
	printf("%zu %d %s 😍\n\n", time, id, str);
	pthread_mutex_unlock(&table->message);

}

void	ft_eat(t_table *table, t_philo **philo, int id)
{
	ft_take_forks(table, philo, id);
	printf("%zu %d is eating\n", ft_usleep((*philo)->table->time_to_eat), id);
//	printf("%d is eating \n", id);
//	ft_usleep((*philo)->table->time_to_eat);
	ft_drop_forks(philo, id);
}

void	ft_sleep(t_philo **philo, int id)
{
	//dprintf(2, "\t->%s\n", __func__);
	printf("%zu %d is sleeping\n", ft_usleep((*philo)->table->time_to_sleep), id);
//	printf("%d is sleeping 😴\n", id);
}

void	ft_think(t_philo **philo, int id)
{
	(void)philo;
	printf("%d is thinking\n", id);
}
