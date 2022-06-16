/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:36:24 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:38:49 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_meals(t_philo *philos, unsigned int nb_philos, long nb_meals)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (philos[i].nb_meals < nb_meals)
			return (0);
		i++;
	}
	return (1);
}

int	check_death(t_philo *philos, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (is_dead(&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	watch_threads(t_util *utils, t_philo *philos, unsigned int nb_philos,
			pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (*philos->stop == 0)
	{
		ft_sleep(4);
		check_death(philos, nb_philos);
		if (*philos->stop == 0 && utils->nb_meals > 0
			&& check_meals(philos, nb_philos, utils->nb_meals))
		{
			*philos->stop = 1;
			ft_sleep(5);
			printf("Everyone ate well\n");
		}
	}
	while (i < nb_philos)
	{
		if (i == 0 && *philos->stop == 1)
			unlock_forks(forks, nb_philos);
		if (pthread_join(philos[i].thread, NULL))
			return (0);
		i++;
	}
	free(philos);
	return (1);
}

void	set_philos(t_philo *philos, t_util *utils, pthread_mutex_t *forks,
			pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < utils->nb_philo)
	{
		philos[i].name = i + 1;
		philos[i].nb_meals = 0;
		philos[i].utils = utils;
		philos[i].print = print;
		pthread_mutex_init(&philos[i].lunch, NULL);
		get_forks(&philos[i], i, forks, utils->nb_philo);
		i++;
	}
}

int	launch_threads(t_util *utils, pthread_mutex_t *forks,
			pthread_mutex_t *print)
{
	t_philo			*philos;
	int				i;
	struct timeval	tm;
	int				stop;

	i = 0;
	stop = 0;
	philos = malloc(sizeof(t_philo) * utils->nb_philo);
	if (!philos)
		return (0);
	set_philos(philos, utils, forks, print);
	gettimeofday(&tm, NULL);
	while (i < utils->nb_philo)
	{
		philos[i].stop = &stop;
		philos[i].ts = tm;
		philos[i].last_meal = get_time();
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			return (0);
		i++;
	}
	return (watch_threads(utils, philos, utils->nb_philo, forks));
}
