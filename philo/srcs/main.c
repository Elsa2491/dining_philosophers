/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/25 11:45:00 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_data(t_data *data, char **argv)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->fork_nb = ft_atoi(argv[1]);
	data->time_before_dying = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	dprintf(2, " Philo num:\t\t%d\n", data->philo_nb);
	dprintf(2, " Fork num:\t\t%d\n", data->philo_nb);
	dprintf(2, " Time before dying:\t%d\n", data->time_before_dying);
	dprintf(2, " Time to eat:\t\t%d\n", data->time_to_eat);
	dprintf(2, " Time to sleep:\t\t%d\n", data->time_to_sleep);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_check_params(argc, argv);
	memset(&data, 0, sizeof(t_data));
	ft_init_data(&data, argv);
}
