/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/27 15:15:41 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free_tab(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		free(table->philo_tab[i]);
		free(table->fork_tab[i]);
		table->fork_tab[i] = NULL;
		table->philo_tab[i++] = NULL;
	}
	free(table->philo_tab);
	free(table->fork_tab);
	table->philo_tab = NULL;
}
