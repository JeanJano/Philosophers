/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:23:34 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 19:27:12 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(char **av, t_parsing *parsing, t_philo **philo, t_mutex *mutex)
{
	int	i;

	parsing->death = 0;
	parsing->have_all_eat = 0;
	parsing->nb_philo = ft_atoi(av[1]);
	parsing->time_die = ft_atoi(av[2]);
	parsing->time_eat = ft_atoi(av[3]);
	parsing->time_sleep = ft_atoi(av[4]);
	if (!av[6])
		parsing->nb_must_eat = ft_atoi(av[5]);
	else
		parsing->nb_must_eat = -1;
	parsing->tab_must_eat = malloc(parsing->nb_philo * sizeof(int));
	if (parsing->tab_must_eat == NULL)
		return ;
	i = 0;
	while (i < parsing->nb_philo)
	{
		parsing->tab_must_eat[i] = 0;
		i++;
	}
	*philo = lst_new(1, parsing, mutex);
}

void	init_philo(t_philo **philo, t_parsing *parsing, t_mutex *mutex)
{
	t_philo	*new;
	int		i;

	i = 2;
	(*philo)->name = 1;
	while (i <= parsing->nb_philo)
	{
		new = lst_new(i, parsing, mutex);
		lstadd_back(philo, new);
		i++;
	}
	new = lst_last(*philo);
	new->next = *philo;
	(*philo)->previous = new;
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_parsing	parsing_struct;
	t_mutex		mutex_struct;

	if (ac < 5 || ac > 6)
		return (1);
	if (parsing(av) == 0)
		return (1);
	init(av, &parsing_struct, &philo, &mutex_struct);
	init_philo(&philo, &parsing_struct, &mutex_struct);
	thread_manage(&philo);
	free_philo(&philo, &parsing_struct);
}
