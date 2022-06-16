/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 06:31:02 by ataji             #+#    #+#             */
/*   Updated: 2022/06/16 06:46:48 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_b.h"

int	main(int ac, char **av)
{
	t_utils			utils;
	sem_t			*print;
	int				ret;

	if (ac < 5 || ac > 6 || !check_args(ac, av, &utils))
	{
		write(2, "Wrong arguments\n", 16);
		return (1);
	}
	if (!utils.nb_meals)
	{
		printf("Everyone ate well, even though no one ate\n");
		return (0);
	}
	ret = 1;
	sem_unlink("print");
	print = sem_open("print", O_CREAT, S_IRWXU | S_IRWXG, 1);
	if (!launch_children(&utils, print))
		ret = 0;
	sem_close(print);
	sem_unlink("print");
	return (ret);
}
