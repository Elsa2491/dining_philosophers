/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_loop_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:31:21 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/25 11:57:22 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//typedef struct s_data t_data;

/*
typedef struct s_fork{
	int	i;
	pthread_mutex_t	mutex;
}t_fork;

typedef struct s_philo {
	int		id;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_meals;
	long		meals_total;
	pthread_t	ph;
	t_fork		*forks_rigth;
	t_fork		*forks_left;
	t_data		*data;
}t_philo;

struct s_data{
	t_philo	*philo;
	t_fork	*table_fork;
	bool	die;
	struct timeval	start;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_time;
};

void	ms_usleep(long	sleep_time, t_philo	*philo)
{
	long 	time;

	time = 0;
	while (time < sleep_time)
	{
		usleep(100);
		// mutxe_die
		if (philo->data.die)
		{
			// unlock mutex
			break ;
		}
		// unlock mutex
	}
}
*/

typedef struct s_counter
{
	pthread_mutex_t	count_mutex;
	int	count;
}		t_counter;

void	*ft_routine(void *data)
{
	pthread_t	tid;
	t_counter	*counter;
	int	 i;

	i = 0;
//	tid = pthread_self();
	counter = (t_counter *)data; 

	pthread_mutex_lock(&counter->count_mutex);
	counter->count = 0;
	pthread_mutex_unlock(&counter->count_mutex);
	while (i < 200)
	{
		pthread_mutex_lock(&counter->count_mutex);
		counter->count += 1;
		pthread_mutex_unlock(&counter->count_mutex);
		i += 1;
	}
//	pthread_mutex_lock(&counter->count_mutex);
//	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	philo[100];
	t_counter	counter;
	int	i = 0;

	pthread_mutex_init(&counter.count_mutex, NULL);
	while (i < 100)
	{
		if (pthread_create(&philo[i], NULL, &ft_routine, &counter) != 0)
			return (1);
		if (philo[i] % 2 == 0)
		{
			dprintf(2, "je suis pair\n");
			usleep(10000);
		}
		dprintf(1, "Thread %d has started\n", i);
		i += 1;
	}
	i = 0;
	while (i < 100)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			dprintf(2, "je suis la\n");
			return (1);
		}
		dprintf(1, "Thread %d has finished execution\n", i);
		i += 1;
	}
	pthread_mutex_lock(&counter.count_mutex);
	printf("Number of count: %d\n", counter.count);
	pthread_mutex_unlock(&counter.count_mutex);
	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}

/*
   i < 400
   Number of count: -589934492
   Number of count: -589934492
   Number of count: -589934492

   i < 251
   Number of count: 725032804
   Number of count: 725032804
 */
