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

void	ft_drop_forks(t_philo **philo, int id);
int	ft_usleep(int millisec);

void	ft_eat(t_philo **philo, int id)
{
	if (pthread_mutex_lock((*philo)->left_f) == 0)
		printf("%d has taken a fork (right) ✅\n", id);
	else // si la fourchette est occupee, je ne rentre pas dans le else parce que pthread ne retourne rien dans ce cas la, donc je reste coincee sur cette meme ligne
		printf("error\n");
	if (pthread_mutex_lock((*philo)->right_f) == 0)
		printf("%d has taken a fork (left) ✅\n", id);
	else
		printf("error\n");
	printf("%d is eating 🥄\n", id);
	ft_usleep((*philo)->table->time_to_eat);
	ft_drop_forks(philo, id);
}

void	ft_drop_forks(t_philo **philo, int id)
{
	if (pthread_mutex_unlock((*philo)->right_f) == 0)
		printf("%d left fork lock ❌\n", id);
	if (pthread_mutex_unlock((*philo)->left_f) == 0)
		printf("%d right fork lock ❌\n", id);
}

void	ft_sleep(t_philo **philo, int id)
{
	//dprintf(2, "\t->%s\n", __func__);
	ft_usleep((*philo)->table->time_to_sleep);
	printf("%d is sleeping 😴\n", id);
}

void	ft_think(t_philo **philo, int id)
{
	(void)philo;
	printf("%d is thinking 💡\n", id);
}
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
//	dprintf(2, "\t->%s\n", __func__);
//	if (id % 2 == 0)
//		ft_sleep(philo_ptr, id);
	while (1)
	{
//		dprintf(2, "id -> %d\n", id);
		ft_think(philo_ptr, id);
		ft_sleep(philo_ptr, id);
		ft_eat(philo_ptr, id);
	}
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

int	ft_get_current_time(void)
{
	struct timeval	time;
	int	convert_millisec;
	int	avoid_division;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("get_current_time() error\n", 2);
	convert_millisec = time.tv_sec * 1000;
	avoid_division = (time.tv_usec * 1001) >> 10;
	return (convert_millisec + avoid_division);
}

int	ft_usleep(int millisec)
{
	int	start;

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
	ft_free_tab(&table);
}
