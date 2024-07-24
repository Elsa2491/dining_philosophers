/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/24 21:24:25 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i += 1;
	return (i);
}

static void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

size_t	ft_get_current_time(void)
{
	struct timeval		time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("get_current_time() error\n", 2);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	ft_usleep(t_table *table, size_t millisec)
{
	size_t	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < millisec && !ft_no_one_died(table))
		usleep(100);
	return (0);
}
