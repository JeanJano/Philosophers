/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:56:56 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 18:27:28 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_int(char *str)
{
	int	convert;
	int	i;

	convert = ft_atoi(str);
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] - 48 != convert % 10)
			return (0);
		convert /= 10;
		i--;
	}
	return (1);
}

int	check_str_if_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_sup_zero(char *str)
{
	if (ft_atoi(str) < 1)
		return (0);
	return (1);
}

int	parsing(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_str_if_digit(av[i]) == 0)
			return (printf("arg accept only digits\n"), 0);
		if (check_if_int(av[i]) == 0)
			return (printf("arg accept only int\n"), 0);
		if ((i == 1 || i == 5) && !check_sup_zero(av[i]))
			return (printf("arg 1 or 5 need to be more than 0\n"), 0);
		i++;
	}
	return (1);
}
