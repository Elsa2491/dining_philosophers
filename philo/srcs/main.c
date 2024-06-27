/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/27 14:49:59 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
void	ft_init_philo_thread(t_philo *philo)
{

}
*/

void	ft_assign_forks(t_table *table) //, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		dprintf(2, "i vaut %d\n", i);
		if (i % 2 == 0)
		{
			dprintf(2, "i modulo 2 ok\n");
//			table->philo_tab[i]->left_f->i = i;
			
		}
		else
			table->philo_tab[i]->right_f->i = i;
		i += 1;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_check_params(argc, argv);
	memset(&table, 0, sizeof(t_table));
	memset(&table.fork, 0, sizeof(t_fork));
	ft_init_table(&table, argv);
	ft_init_philos_and_forks(&table); //, table.philo);
//	ft_assign_forks(&table); // , table.philo);
//	ft_init_philo_thread(&table.philo);
	ft_free_tab(&table);
}
