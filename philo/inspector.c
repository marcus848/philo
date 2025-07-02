/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:11:54 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 20:33:39 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_full(t_table *t)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < t->n_philos)
	{
		if (t->philos[i].meals_eaten >= t->times_must_eat)
			count++;
		i++;
	}
	if (count == t->n_philos)
		return (1);
	return (0);
}

void	*inspector(void *arg)
{
	t_table	*t;

	t = (t_table *) arg;
	if (t->times_must_eat <= 0)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&t->table_lock);
		if (t->is_ended)
		{
			pthread_mutex_unlock(&t->table_lock);
			break ;
		}
		pthread_mutex_unlock(&t->table_lock);
		if (all_full(t))
		{
			pthread_mutex_lock(&t->table_lock);
			t->is_ended = 1;
			pthread_mutex_unlock(&t->table_lock);
		}
		usleep(500);
	}
	return (NULL);
}
