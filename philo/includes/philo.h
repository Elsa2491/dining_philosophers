/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:37:27 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/25 10:19:48 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structures.h"
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
//# include <pthread.h>
# include <sys/wait.h>
# include <sys/types.h>

# define WARNING         " → Warning\n"
# define ARROW  "\t→ "

int	ft_atoi(char *str);
void	ft_check_params(int argc, char **argv);
void	ft_print_missing_param(int *tab);
#endif
