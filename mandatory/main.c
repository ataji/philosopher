/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:36:12 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:38:34 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_util			utils;
	int				ret;
	pthread_mutex_t	*forks;
	pthread_mutex_t	prt;

	if (ac == 5 || ac == 6)
	{
		if (!check_error(av, ac))
			return (0);
		else
			insert_philo(&utils, av, ac);
	}
	else
		return (printf("Wrong params!\n"), 0);
	ret = 1;
	forks = init_forks(&utils);
	pthread_mutex_init(&prt, NULL);
	if (!forks || !launch_threads(&utils, forks, &prt))
		ret = 0;
	destroy_forks(forks, &utils);
	pthread_mutex_destroy(&prt);
	return (ret);
}
