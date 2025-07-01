/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:48:11 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 18:54:09 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		pthread_mutex_destroy(&t->forks[i]);
		pthread_mutex_destroy(&t->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&t->write_lock);
	pthread_mutex_destroy(&t->table_lock);
	free(t->forks);
	free(t->philos);
	free(t);
}
