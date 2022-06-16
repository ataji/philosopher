/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:36:19 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:38:43 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_atoi(char *str)
{
	int				i;
	long long int	n;
	int				signe;

	i = 0;
	n = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (ERR);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + str[i++] - '0';
	if (str[i] == '\0' && str[i - 1] == '-')
		return (ERR);
	if (str[i] && (str[i] <= '0' || str[i] >= '9'))
		return (ERR);
	return (n * signe);
}

int	check_error(char **av, int ac)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_atoi(av[i]) == ERR || ft_atoi(av[i]) == 0)
			return (printf("Wrong params!\n"), 0);
	}
	return (1);
}

void	insert_philo(t_util *utils, char **av, int ac)
{
	utils->nb_philo = ft_atoi(av[1]);
	utils->tt_die = ft_atoi(av[2]);
	utils->tt_eat = ft_atoi(av[3]);
	utils->tt_sleep = ft_atoi(av[4]);
	if (ac == 6)
		utils->nb_meals = ft_atoi(av[5]);
}
