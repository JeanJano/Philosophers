/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:51:09 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 20:42:08 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*message(t_philo *philo, int name, char *message)
{
	pthread_mutex_lock(&philo->mutex->print_mutex);
	pthread_mutex_lock(&philo->mutex->death_mutex);
	if (philo->parsing->death > 0)
	{
		pthread_mutex_unlock(&philo->mutex->death_mutex);
		pthread_mutex_unlock(&philo->mutex->print_mutex);
		return (NULL);
	}
	printf("%ld %d %s\n", get_now() - philo->start_time, name, message);
	pthread_mutex_unlock(&philo->mutex->death_mutex);
	pthread_mutex_unlock(&philo->mutex->print_mutex);
	return ((void *)1);
}

void	message_death(t_philo *philo)
{
	if (philo->death > 0)
		return ;
	pthread_mutex_lock(&philo->mutex->eat_mutex);
	if (philo->parsing->have_all_eat == 1)
	{
		pthread_mutex_unlock(&philo->mutex->eat_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->mutex->death_mutex);
	philo->parsing->death = 1;
	philo->death++;
	printf("%ld %d died\n", get_now() - philo->start_time, philo->name);
	pthread_mutex_unlock(&philo->mutex->eat_mutex);
	pthread_mutex_unlock(&philo->mutex->death_mutex);
}
