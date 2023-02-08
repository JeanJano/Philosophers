/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:26:46 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/04 19:47:08 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h> 
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_parsing
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_must_eat;
	int	*tab_must_eat;
	int	death;
	int	have_all_eat;
}		t_parsing;

typedef struct s_mutex
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	var_mutex;
	pthread_mutex_t	eat_mutex;
}					t_mutex;

typedef struct s_philo
{
	int				name;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	thread_mutex;
	t_mutex			*mutex;
	t_parsing		*parsing;
	long int		start_time;
	long int		last_eat;
	int				death;
	int				eat_incr;
	struct s_philo	*next;
	struct s_philo	*previous;
}					t_philo;

int			parsing(char **av);

void		thread_manage(t_philo **data);
void		thread_create(t_philo *philo);
void		thread_join(t_philo *philo);
void		mutex_destroy(t_philo *philo);
void		mutex_init(t_philo *philo);

void		*routine(void *arg);
void		table(t_philo *philo);
int			take_fork(t_philo *philo, int name);
int			sleeping(t_philo *philo);
int			eating(t_philo *philo, t_philo *philo_next);
int			thinking(t_philo *philo);
int			is_died(t_philo *philo);
int			is_alive(t_philo *philo);
int			have_all_eat(t_philo *philo);
t_philo		*priority(t_philo *philo);
void		one_philo(t_philo *philo);
int			fork_manage(t_philo *philo, t_philo *philo_next);
int			fork_odd(t_philo *philo, t_philo *philo_next);
int			fork_even(t_philo *philo, t_philo *philo_next);
int			check_all_eat(t_philo *philo, t_philo *philo_next);

void		*message(t_philo *philo, int name, char *message);
void		message_death(t_philo *philo);

long int	get_now(void);
int			ft_usleep(long int time, t_philo *philo);

int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);
int			is_even(int nb);

t_philo		*lst_new(int name, t_parsing *parsing, t_mutex *mutex);
t_philo		*lst_last(t_philo *lst);
void		lstadd_back(t_philo **lst, t_philo *new);
int			lst_size(t_philo *lst);

void		free_philo(t_philo **philo, t_parsing *parsing);
void		free_thread(t_philo *philo, int i);

#endif