/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:30:57 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:46:53 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_b.h"

unsigned long	get_ts(struct timeval ts)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000)
			- (ts.tv_sec * 1000 + ts.tv_usec / 1000));
}

int	is_dead(t_philo *philo)
{
	if (*philo->stop == true)
		return (1);
	sem_wait(philo->lunch);
	if (get_time() - philo->last_meal >= philo->utils->tt_die)
	{
		sem_post(philo->lunch);
		if (*philo->stop == false)
		{
			*philo->stop = true;
			sem_wait(philo->print);
			printf("%lums %zu died\n", get_ts(philo->ts), philo->name);
		}
		return (1);
	}
	sem_post(philo->lunch);
	return (0);
}

int	fall_asleep(t_philo *philo)
{
	if (*philo->stop == true)
		return (0);
	sem_wait(philo->print);
	printf("%lums %zu is sleeping\n", get_ts(philo->ts), philo->name);
	sem_post(philo->print);
	ft_sleep(philo->utils->tt_sleep);
	if (*philo->stop == true)
		return (0);
	sem_wait(philo->print);
	printf("%lums %zu is thinking\n", get_ts(philo->ts), philo->name);
	sem_post(philo->print);
	return (1);
}

int	eat(t_philo *philo)
{
	sem_wait(philo->lunch);
	philo->last_meal = get_time();
	sem_wait(philo->print);
	printf("%lums %zu is eating\n", get_ts(philo->ts), philo->name);
	sem_post(philo->print);
	sem_post(philo->lunch);
	ft_sleep(philo->utils->tt_eat);
	philo->nb_meals += 1;
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (*philo->stop == true)
		return (0);
	return (1);
}

void	*live(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->name % 2)
		ft_sleep(2);
	while (*philo->stop == false)
	{
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		if (!fall_asleep(philo))
			break ;
	}
	return (NULL);
}
