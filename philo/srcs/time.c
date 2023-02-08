/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:37:40 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 18:38:45 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

int	ft_usleep(long int time, t_philo *philo)
{
	struct timeval	tv;
	struct timeval	start;
	long int		laptime;

	gettimeofday(&start, NULL);
	laptime = 0;
	while (laptime < time)
	{
		pthread_mutex_lock(&philo->mutex->death_mutex);
		if (philo->parsing->death > 0)
		{
			pthread_mutex_unlock(&philo->mutex->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->mutex->death_mutex);
		gettimeofday(&tv, NULL);
		laptime = (tv.tv_sec - start.tv_sec) * 1000
			+ (tv.tv_usec - start.tv_usec) / 1000;
		usleep(50);
	}
	return (1);
}
