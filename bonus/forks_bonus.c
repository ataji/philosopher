/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:29:58 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:43:39 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_b.h"

int	take_forks(t_philo *philo)
{
	if (*philo->stop == true)
		return (0);
	sem_wait(philo->forks);
	if (*philo->stop == true)
		return (0);
	sem_wait(philo->print);
	printf("%lums %zu has taken a fork\n", get_ts(philo->ts), philo->name);
	sem_post(philo->print);
	sem_wait(philo->forks);
	if (*philo->stop == true)
		return (0);
	sem_wait(philo->print);
	printf("%lums %zu has taken a fork\n", get_ts(philo->ts), philo->name);
	sem_post(philo->print);
	return (1);
}

sem_t	*init_forks(t_utils *utils)
{
	sem_t	*forks;

	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, S_IRWXU | S_IRWXG, utils->nb_philo);
	return (forks);
}
