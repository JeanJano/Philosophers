/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:28:00 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 19:41:34 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	have_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->parsing->nb_philo)
	{
		pthread_mutex_lock(&philo->thread_mutex);
		if (philo->eat_incr >= philo->parsing->nb_must_eat)
			philo->parsing->tab_must_eat[i] = 1;
		pthread_mutex_unlock(&philo->thread_mutex);
		i++;
		philo = philo->next;
	}
}

int	have_all_eat(t_philo *philo)
{
	int	i;
	int	eat;

	if (philo->parsing->nb_must_eat == -1)
		return (0);
	i = 0;
	eat = 0;
	have_eat(philo);
	while (i < philo->parsing->nb_philo)
	{
		pthread_mutex_lock(&philo->thread_mutex);
		if (philo->parsing->tab_must_eat[i] == 1)
			eat++;
		pthread_mutex_unlock(&philo->thread_mutex);
		i++;
	}
	if (eat == philo->parsing->nb_philo)
	{
		pthread_mutex_lock(&philo->mutex->eat_mutex);
		philo->parsing->have_all_eat = 1;
		pthread_mutex_unlock(&philo->mutex->eat_mutex);
		return (1);
	}
	return (0);
}

void	table(t_philo *philo)
{
	if (philo->parsing->death > 0 || philo->death > 0)
		return ;
	while (1)
	{
		if (philo->parsing->nb_must_eat > 0)
		{
			if (have_all_eat(philo) == 1)
				break ;
		}
		if (is_died(philo) == 0)
			break ;
		philo = philo->next;
	}
}

int	fork_manage(t_philo *philo, t_philo *philo_next)
{
	if (is_even(philo->name) == 1)
	{
		if (fork_even(philo, philo_next) == 0)
			return (0);
	}
	else
	{
		if (fork_odd(philo, philo_next) == 0)
			return (0);
	}
	return (1);
}

void	one_philo(t_philo *philo)
{
	take_fork(philo, philo->name);
	pthread_mutex_unlock(&philo->fork_mutex);
	ft_usleep(philo->parsing->time_die, philo);
	message_death(philo);
}
