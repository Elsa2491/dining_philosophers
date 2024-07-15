/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/15 15:14:29 by eltouma          ###   ########.fr       */
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
	size_t				convert_millisec;
	size_t				avoid_division;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("get_current_time() error\n", 2);
		// free ce qu'il faut
	convert_millisec = time.tv_sec * 1000;
	avoid_division = (time.tv_usec * 1048) >> 20;
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
