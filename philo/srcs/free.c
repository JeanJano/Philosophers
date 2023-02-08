/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:35:38 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/03 17:16:25 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo **philo, t_parsing *parsing)
{
	t_philo	*tmp;
	int		i;

	tmp = *philo;
	i = 0;
	while (i < parsing->nb_philo - 1)
	{
		tmp = (*philo)->next;
		free(*philo);
		*philo = tmp;
		i++;
	}
	free(*philo);
	free(parsing->tab_must_eat);
}

void	free_thread(t_philo *philo, int i)
{
	while (i > 0)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			return ;
		philo = philo->previous;
		i--;
	}
}
