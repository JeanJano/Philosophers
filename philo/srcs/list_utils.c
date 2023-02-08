/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:58:54 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 18:34:24 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*lst_new(int name, t_parsing *parsing, t_mutex *mutex)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	res->name = name;
	res->next = NULL;
	res->previous = NULL;
	res->parsing = parsing;
	res->mutex = mutex;
	res->start_time = get_now();
	res->last_eat = -1;
	res->eat_incr = 0;
	res->death = parsing->death;
	return (res);
}

t_philo	*lst_last(t_philo *lst)
{
	t_philo	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (*lst)
	{
		last = lst_last((*lst));
		new->previous = last;
		last->next = new;
	}
	else
		*lst = new;
}

int	lst_size(t_philo *lst)
{
	t_philo	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (lst->next != tmp)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
