/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:40:49 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/24 19:31:13 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i += 1;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	base;

	i = 0;
	base = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) 
		i += 1;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		base = base * 10 + str[i] - 48;
		i += 1;
	}
	return (base);
}

int	ft_check_params(int argc, char **argv)
{
	int	i;
	int	j;
	int	size;
	int	tab[argc - 1];
	
	i = 1;
	j = 0;
	size = 0;
	if (argc != 5)
		return (1);
	while (i < argc)
	{
		if (ft_is_num(argv[i]) && ft_atoi(argv[i]) > 0)
			tab[j++] = ft_atoi(argv[i]);
		i += 1;
	}
	i = 0;
	while (i < j)
	{
		size += 1;
		i += 1;
	}
	if (size != argc - 1)
		return (dprintf(2, "No mercy!\n"), 1);
	else
		return (dprintf(2, "Get some rest!\n"), 0);

}

/*
int	ft_check_params(int argc, char **argv)
{
	int	i;
	
	i = 1;
	if (argc != 5)
		return (1);
	while (i < argc)
	{
		if (!ft_is_num(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (dprintf(2, "No mercy!\n"), 1);
		i += 1;
	}
	return (dprintf(2, "Get some rest!\n"), 0);
}
*/ 
