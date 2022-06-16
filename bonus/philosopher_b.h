/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_b.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:32:14 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:45:01 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_B_H
# define PHILOSOPHER_B_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>

# define LEFT 0
# define RIGHT 1
# define IS_DEAD 0
# define ATE_ENOUGH 1
# define ERR 2

typedef struct s_utils
{
	unsigned int	nb_philo;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	long			nb_meals;
}	t_utils;

typedef struct s_philo
{
	size_t			name;
	long			nb_meals;
	bool			*stop;
	t_utils			*utils;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*lunch;
	sem_t			*sync;
	char			*lunch_name;
	size_t			last_meal;
	struct timeval	ts;
	int				pid;
}	t_philo;

int				main(int argc, char **argv);
void			unlock_sync(sem_t *sync, unsigned int nb_philos);
size_t			get_time(void);
void			ft_sleep(size_t ms);
void			kill_children(t_philo *philos, unsigned int nb_philos);
int				watch_children(t_philo *philos, unsigned int nb_philos);
void			process(t_philo *philo);
int				set_philos(t_philo *philos, t_utils *utils, sem_t *print);
int				launch_children(t_utils *utils, sem_t *print);
int				take_forks(t_philo *philo);
sem_t			*init_forks(t_utils *utils);
unsigned long	get_ts(struct timeval ts);
int				is_dead(t_philo *philo);
int				fall_asleep(t_philo *philo);
int				eat(t_philo *philo);
void			*live(void *arg);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
bool			check_args(int ac, char **av, t_utils *utils);
int				ft_strlen(const char *str);

#endif
