/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/07/15 15:07:33 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_message(char *str, t_table *table, int id)
{
	size_t	timestamps;

	pthread_mutex_lock(&table->message);
	timestamps = ft_get_current_time() - table->program_start;
/*
	dprintf(2, "\t\t-> get_current_time in %s = %zu\n", __func__, ft_get_current_time());
	dprintf(2, "\t\t-> ICI table->program_start %zu\n", table->program_start);
	dprintf(2, "\t\t-> table->program_start %zu\n", table->program_start);
	dprintf(2, "\t\t-> time %zu\n", timestamps);
*/
	printf("%zu %d %s\n", timestamps >> 10, id, str);
	pthread_mutex_unlock(&table->message);
}

void	ft_print_header(void)
{
	printf("\n\e[2m ####################################\e[0m");
	printf("\e[2m####################################\n\n\e[0m");
}

void	ft_print_footer(void)
{
	ft_print_header();
	exit(EXIT_FAILURE);
}

void	ft_print_missing_param(int *tab)
{
	if (tab)
		free(tab);
	ft_print_header();
	printf("\033[%dm\e[1m%s\e\033[0m", 31, WARNING);
	printf(" It seems something went wrong.\n");
	printf(" You must enter at least 4 parameters.\n");
	printf(" Each parameter should be an int > 0.");
	printf(" Please, see the example below:\n");
	printf("\033[%dm\e[1m%s\e\033[0m", 32, ARROW);
	printf(" \033[%dm./philo\033[0m philo_nb time_before_dying", 33);
	printf(" time_to_eat time_to_sleep [number of meals]\n");
	ft_print_footer();
}
