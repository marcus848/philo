/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:19:49 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 19:48:43 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac != 5 && ac != 6)
	{
		printf("Use: %s <n_filos> <die> <eat> <sleep> [must_eat]\n", av[0]);
		return (1);
	}
	if (!check_input(av))
	{
		printf("Just positive numbers accept\n");
		return (1);
	}
	table = init_table(ac, av);
	if (!table)
		return (1);
	if (start_threads(table))
	{
		printf("[ERROR] Create Threads\n");
		free_table(table);
		return (1);
	}
	free_table(table);
	return (0);
}
