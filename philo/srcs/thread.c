/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:07:51 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 19:32:10 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_philo	*philo_next;

	philo = (t_philo *)arg;
	if (philo->parsing->nb_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	philo_next = priority(philo);
	if (is_even(philo->name) == 0)
		ft_usleep(philo->parsing->time_eat / 2, philo);
	while (1)
	{
		if (fork_manage(philo, philo_next) == 0)
			break ;
		if (eating(philo, philo_next) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
		if (thinking(philo) == 0)
			break ;
	}
	return (NULL);
}

void	thread_manage(t_philo **philo)
{
	t_philo	*tmp;

	tmp = *philo;
	mutex_init(tmp);
	tmp = *philo;
	thread_create(tmp);
	tmp = *philo;
	if (tmp->parsing->nb_philo > 1)
		table(tmp);
	thread_join(tmp);
	tmp = *philo;
	mutex_destroy(tmp);
}
