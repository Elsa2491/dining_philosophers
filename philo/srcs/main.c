/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/25 16:27:55 by eltouma          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_table	table;

	ft_check_params(argc, argv);
	memset(&table, 0, sizeof(t_table));
	ft_init_table(&table, argv);
}
