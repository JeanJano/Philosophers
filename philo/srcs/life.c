/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:54:00 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 20:34:03 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo, int name)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (message(philo, name, "has taken a fork") == NULL)
		return (0);
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (message(philo, philo->name, "is sleeping") == NULL)
		return (0);
	if (ft_usleep(philo->parsing->time_sleep, philo) == 0)
		return (0);
	return (1);
}

int	eating(t_philo *philo, t_philo *philo_next)
{
	pthread_mutex_lock(&philo->mutex->eat_mutex);
	philo->last_eat = get_now();
	pthread_mutex_unlock(&philo->mutex->eat_mutex);
	if (message(philo, philo->name, "is eating") == NULL)
	{
		pthread_mutex_unlock(&philo_next->fork_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		return (0);
	}
	if (check_all_eat(philo, philo_next) == 0)
		return (0);
	if (ft_usleep(philo->parsing->time_eat, philo) == 0)
	{
		pthread_mutex_unlock(&philo_next->fork_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo_next->fork_mutex);
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->thread_mutex);
	philo->eat_incr++;
	pthread_mutex_unlock(&philo->thread_mutex);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (message(philo, philo->name, "is thinking") == NULL)
		return (0);
	if (is_even(philo->parsing->nb_philo) == 0)
	{
		if (ft_usleep(philo->parsing->time_die - philo->parsing->time_eat
				- philo->parsing->time_sleep - 30, philo) == 0)
			return (0);
	}
	return (1);
}

int	is_died(t_philo *philo)
{
	long int	last_eat;

	pthread_mutex_lock(&philo->mutex->eat_mutex);
	if (philo->last_eat == -1)
		last_eat = 0;
	else
		last_eat = get_now() - philo->last_eat;
	pthread_mutex_unlock(&philo->mutex->eat_mutex);
	if (last_eat > (long int)philo->parsing->time_die)
	{
		message_death(philo);
		return (0);
	}
	return (1);
}
