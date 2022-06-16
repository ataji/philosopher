/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:32:58 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:38:21 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	unlock_forks(pthread_mutex_t *forks, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
		pthread_mutex_unlock(&forks[i++]);
}

int	take_forks(t_philo *philo, pthread_mutex_t *forkl,
			pthread_mutex_t *forkr)
{
	if (*philo->stop == 1)
		return (0);
	pthread_mutex_lock(forkl);
	if (*philo->stop == 1)
		return (0);
	pthread_mutex_lock(philo->print);
	printf("%lums %zu has taken a fork\n", get_ts(philo->ts), philo->name);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(forkr);
	if (*philo->stop == 1)
		return (0);
	pthread_mutex_lock(philo->print);
	printf("%lums %zu has taken a fork\n", get_ts(philo->ts), philo->name);
	pthread_mutex_unlock(philo->print);
	return (1);
}

pthread_mutex_t	*init_forks(t_util *utils)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * utils->nb_philo);
	if (!forks)
		return (0);
	while (i < utils->nb_philo)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

void	destroy_forks(pthread_mutex_t *forks, t_util *utils)
{
	int	i;

	i = 0;
	while (i < utils->nb_philo)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
}

void	get_forks(t_philo *philo, size_t index, pthread_mutex_t *forks,
				unsigned int nb_philo)
{
	if (nb_philo == 1)
	{
		philo->fork[LEFT] = &forks[0];
		philo->fork[RIGHT] = &forks[0];
	}
	if (index == 0)
	{
		philo->fork[LEFT] = &forks[nb_philo - 1];
		philo->fork[RIGHT] = &forks[0];
	}
	else
	{
		philo->fork[LEFT] = &forks[index - 1];
		philo->fork[RIGHT] = &forks[index];
	}
}
