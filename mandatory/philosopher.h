/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:36:32 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:38:15 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define ERR -1
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>

# define LEFT 0
# define RIGHT 1

typedef struct s_util
{
	int				nb_philo;
	int				tt_eat;
	int				tt_sleep;
	int				tt_die;
	int				nb_meals;
}t_util;

typedef struct s_philo
{
	size_t			name;
	int				*stop;
	long			nb_meals;
	t_util			*utils;
	pthread_mutex_t	*fork[2];
	pthread_mutex_t	*print;
	pthread_mutex_t	lunch;
	size_t			last_meal;
	struct timeval	ts;
	pthread_t		thread;
}	t_philo;

long			ft_atoi(char *str);
int				check_error(char **av, int ac);
void			insert_philo(t_util *utils, char **av, int ac);
int				main(int argc, char **argv);
size_t			get_time(void);
void			ft_sleep(size_t ms);
int				check_death(t_philo *philos, unsigned int nb_philos);
int				check_meals(t_philo *philos, unsigned int nb_philos,
					long nb_meals);
void			set_philos(t_philo *philos, t_util *utils,
					pthread_mutex_t *forks, pthread_mutex_t *print);
int				watch_threads(t_util *utils, t_philo *philos,
					unsigned int nb_philos, pthread_mutex_t *forks);
int				launch_threads(t_util *utils, pthread_mutex_t *forks,
					pthread_mutex_t *print);
void			unlock_forks(pthread_mutex_t *forks, unsigned int nb_philos);
int				take_forks(t_philo *philo, pthread_mutex_t *forkl,
					pthread_mutex_t *forkr);
pthread_mutex_t	*init_forks(t_util *utils);
void			destroy_forks(pthread_mutex_t *forks, t_util *utils);
void			get_forks(t_philo *philo, size_t index, pthread_mutex_t *forks,
					unsigned int nb_philo);
unsigned long	get_ts(struct timeval ts);
int				is_dead(t_philo *philo);
int				fall_asleep(t_philo *philo);
int				eat(t_philo *philo);
void			*routine(void *arg);

#endif