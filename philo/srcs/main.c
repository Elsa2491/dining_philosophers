/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/27 21:21:40 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_take_forks(t_philo **philo)
{
	dprintf(2, "\t->%s\n", __func__);
	if (pthread_mutex_lock((*philo)->left_f) == 0)
		printf("j'ai pris ma fourchette gauche\n");
	else // si la fourchette est occupee, je ne rentre pas dans le else parce que pthread ne retourne rien dans ce cas la, donc je reste coincee sur cette meme ligne
		printf("error\n");
	if (pthread_mutex_lock((*philo)->right_f) == 0)
		printf("j'ai pris ma fourchette right\n");
	else
		printf("error\n");
	printf("je commence a manger\n");
	usleep(300000);
//	dprintf(2, "time_to_eat %d\n", (*philo)->table->time_to_eat);
//	usleep((*philo)->table->time_to_eat);
	if (pthread_mutex_unlock((*philo)->right_f) == 0)
		printf("j'ai repose ma fourchette droite\n");
	if (pthread_mutex_unlock((*philo)->left_f) == 0)
		printf("j'ai repose ma fourchette gauche\n");

}

void	*ft_routine(void *philo)
{
	dprintf(2, "\t->%s\n", __func__);
//	int	i = 0;
	while (1)
	{
		ft_take_forks(philo);
//		ft_eat();
//		ft_drop_forks();
//		ft_sleep();
//		ft_think();
	//	i += 1;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_check_params(argc, argv);
	memset(&table, 0, sizeof(t_table));
	ft_init_table(&table, argv);
	ft_init_forks(&table);
	ft_init_philos(&table);
	ft_init_threads(&table);
	//	ft_init_philos_and_forks(&table); //, table.philo);
	//	ft_assign_forks(&table); // , table.philo);
	//	ft_init_philo_thread(&table.philo);
	ft_free_tab(&table);
}
