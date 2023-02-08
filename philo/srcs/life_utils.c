/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:29:54 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 19:46:49 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_even(t_philo *philo, t_philo *philo_next)
{
	if (take_fork(philo, philo->name) == 0)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		return (0);
	}
	if (take_fork(philo_next, philo->name) == 0)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo_next->fork_mutex);
		return (0);
	}
	return (1);
}

int	fork_odd(t_philo *philo, t_philo *philo_next)
{
	if (take_fork(philo_next, philo->name) == 0)
	{
		pthread_mutex_unlock(&philo_next->fork_mutex);
		return (0);
	}
	if (take_fork(philo, philo->name) == 0)
	{
		pthread_mutex_unlock(&philo_next->fork_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		return (0);
	}
	return (1);
}

int	check_all_eat(t_philo *philo, t_philo *philo_next)
{
	pthread_mutex_lock(&philo->mutex->eat_mutex);
	if (philo->parsing->have_all_eat == 1)
	{
		pthread_mutex_unlock(&philo->mutex->eat_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo_next->fork_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->mutex->eat_mutex);
	return (1);
}

t_philo	*priority(t_philo *philo)
{
	if (is_even(philo->name) == 1)
		return (philo->next);
	else
		return (philo->previous);
}
