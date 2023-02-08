/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:13:53 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 19:24:23 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->parsing->nb_philo)
	{
		if (pthread_create(&philo->thread, NULL, &routine, (void *)philo) != 0)
		{
			free_thread(philo, i);
			return ;
		}
		philo = philo->next;
		i++;
	}
}

void	thread_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->parsing->nb_philo)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			return ;
		philo = philo->next;
		i++;
	}
}

void	mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->mutex->print_mutex);
	pthread_mutex_destroy(&philo->mutex->var_mutex);
	pthread_mutex_destroy(&philo->mutex->eat_mutex);
	pthread_mutex_destroy(&philo->mutex->death_mutex);
	while (i < philo->parsing->nb_philo)
	{
		pthread_mutex_destroy(&philo->thread_mutex);
		pthread_mutex_destroy(&philo->fork_mutex);
		philo = philo->next;
		i++;
	}
}

void	mutex_init(t_philo *philo)
{
	int	i;

	pthread_mutex_init(&philo->mutex->print_mutex, NULL);
	pthread_mutex_init(&philo->mutex->var_mutex, NULL);
	pthread_mutex_init(&philo->mutex->eat_mutex, NULL);
	pthread_mutex_init(&philo->mutex->death_mutex, NULL);
	i = 0;
	while (i < philo->parsing->nb_philo)
	{
		pthread_mutex_init(&philo->thread_mutex, NULL);
		pthread_mutex_init(&philo->fork_mutex, NULL);
		philo = philo->next;
		i++;
	}
}
