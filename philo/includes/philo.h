/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:37:27 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/18 11:39:03 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structures.h"
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
//# include <pthread.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>

# define WARNING         " → Warning\n"
# define ARROW  "\t→ "

// 	Parsing
int		ft_atoi(char *str);
void	ft_check_params(int argc, char **argv);
void	ft_print_missing_param(int *tab);

//	Clean
void	ft_free_tab(t_table *table);

//	Init
void	ft_init_table(t_table *table, char **argv);
void	ft_init_philos(t_table *table);
void	ft_init_forks(t_table *table);
void	ft_init_threads(t_table *table);

//	Actions
void	*ft_routine(void *args);
void	ft_monitoring(t_table *table, t_philo **philo);
void	ft_eat(t_table *table, t_philo **philo, int id);
void	ft_sleep(t_table *table, t_philo **philo, int id);
void	ft_think(t_table *table, int id);
void	ft_print_message(char *str, t_table *table, int id);

//	Check if someone died
int		ft_no_one_died(t_table *table);

//	Time
size_t	ft_usleep(size_t millisec);
size_t	ft_get_current_time(void);
#endif
