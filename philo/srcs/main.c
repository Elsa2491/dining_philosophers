/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/02 19:00:11 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_no_one_died(t_table *table)
{
	int i = 0;
	pthread_mutex_lock(&table->dead_lock);	
	while (i < table->philo_nb)
	{
		if (table->philo_tab[i]->table->is_dead == 1)
		{
			pthread_mutex_unlock(&table->dead_lock);	
			return (1);
		}
		i += 1;
	}
	pthread_mutex_unlock(&table->dead_lock);	
	return (0);
}

/*
int	ft_no_one_died(t_philo **philo)
{
	int i = 0;
	pthread_mutex_lock((*philo)->dead_lock);	
	while (i < (*philo)->table->philo_nb)
	{
		if ((*philo)->is_dead == 1)
		{
			pthread_mutex_unlock((*philo)->dead_lock);	
			return (1);
		}
		i += 1;
	}
	pthread_mutex_unlock((*philo)->dead_lock);	
	return (0);
}

*/
void	*ft_routine(void *args)
{
	t_philo **philo_ptr;
	t_philo	*philo;
	t_table	*table;
	int	id;

	philo_ptr = (t_philo **)args;
	philo = *philo_ptr;
	table = philo->table;
	id = philo_ptr - table->philo_tab;
	if (id % 2 == 0)
		usleep(1);
	//		ft_sleep(philo_ptr, id);
	while (!ft_no_one_died(table))
	//while (1)
	{
		ft_eat(table, philo_ptr, id);
		ft_sleep(table, philo_ptr, id);
		ft_think(table, philo_ptr, id);
	}
	return (philo);
}

void	ft_handle_one_philo(t_table *table)
{
	if (table->time_before_dying < table->time_to_eat)
	{
		ft_usleep(table->time_before_dying);
		exit (1);
	}
}

void	ft_destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
		pthread_mutex_destroy(table->fork_tab[i++]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i += 1;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

size_t	ft_get_current_time(void)
{
	struct timeval	time;
	size_t	convert_millisec;
	size_t	avoid_division;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("get_current_time() error\n", 2);
	convert_millisec = time.tv_sec * 1000;
	avoid_division = (time.tv_usec * 1001) >> 10;
	//dprintf(2, "COUCOU \t%s -> %zu\n", __func__, (convert_millisec + avoid_division));
	return (convert_millisec + avoid_division);
}

size_t	ft_usleep(size_t millisec)
{
	size_t	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < millisec)
		usleep(500);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_check_params(argc, argv);
	memset(&table, 0, sizeof(t_table));
	ft_init_table(&table, argv);
	ft_init_forks(&table);
	ft_init_philos(&table);
	if (table.philo_nb == 1)
		ft_handle_one_philo(&table);
	ft_init_threads(&table);
	ft_destroy_mutex(&table);
	pthread_mutex_destroy(&table.message);
	//pthread_mutex_destroy(&table.dead_lock);
//	pthread_mutex_destroy(&table.dead_lock);
	ft_free_tab(&table);
}
