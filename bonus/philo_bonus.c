/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:31:09 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:44:25 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_b.h"

void	kill_children(t_philo *philos, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		sem_close(philos[i].lunch);
		sem_unlink(philos[i].lunch_name);
		free(philos[i].lunch_name);
		i++;
	}
}

int	watch_children(t_philo *philos, unsigned int nb_philos)
{
	size_t	nb_full;
	int		status;

	nb_full = 0;
	while (philos->utils->nb_meals > 0 && nb_full != nb_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != ATE_ENOUGH)
			break ;
		nb_full++;
	}
	if (philos->utils->nb_meals < 0)
		waitpid(-1, &status, 0);
	kill_children(philos, nb_philos);
	if (philos->utils->nb_meals && nb_full == nb_philos)
		printf("Everyone ate well\n");
	sem_close(philos->forks);
	sem_unlink("forks");
	sem_close(philos->sync);
	sem_unlink("sync");
	sem_post(philos->print);
	free(philos);
	return (1);
}

void	process(t_philo *philo)
{
	pthread_t	thread;
	bool		stop;

	stop = false;
	philo->stop = &stop;
	sem_wait(philo->sync);
	philo->last_meal = get_time();
	if (pthread_create(&thread, NULL, &live, philo)
		|| pthread_detach(thread))
		exit(ERR);
	while (1)
	{
		ft_sleep(4);
		if (is_dead(philo))
			exit(IS_DEAD);
		else if (philo->utils->nb_meals > 0
			&& philo->nb_meals >= philo->utils->nb_meals)
			exit(ATE_ENOUGH);
	}	
}

int	set_philos(t_philo *philos, t_utils *utils, sem_t *print)
{
	size_t	i;
	sem_t	*forks;
	char	*concat;

	i = 0;
	forks = init_forks(utils);
	if (!forks)
		return (0);
	while (i < utils->nb_philo)
	{
		philos[i].name = i + 1;
		philos[i].nb_meals = 0;
		philos[i].utils = utils;
		philos[i].print = print;
		philos[i].forks = forks;
		concat = ft_itoa(i);
		philos[i].lunch_name = ft_strjoin("lunch_", concat);
		free(concat);
		sem_unlink(philos[i].lunch_name);
		philos[i].lunch = sem_open(philos[i].lunch_name, O_CREAT,
				S_IRWXU | S_IRWXG, 1);
		i++;
	}
	return (1);
}

int	launch_children(t_utils *utils, sem_t *print)
{
	t_philo			*philos;
	size_t			i;
	sem_t			*sync;
	struct timeval	ts;

	i = 0;
	sync = sem_open("sync", O_CREAT, S_IRWXU | S_IRWXG, 0);
	philos = malloc(sizeof(t_philo) * utils->nb_philo);
	if (!philos || !set_philos(philos, utils, print))
		return (0);
	gettimeofday(&ts, NULL);
	while (i < utils->nb_philo)
	{
		philos[i].sync = sync;
		philos[i].pid = fork();
		philos[i].ts = ts;
		if (!philos[i].pid)
			process(&philos[i]);
		else if (philos[i].pid < 0)
			return (0);
		i++;
	}
	unlock_sync(sync, utils->nb_philo);
	return (watch_children(philos, utils->nb_philo));
}
