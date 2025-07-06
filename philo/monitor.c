/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:36:51 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 20:41:43 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *p)
{
	unsigned long	now;

	pthread_mutex_lock(&p->meal_lock);
	now = get_time_in_ms();
	if (now - p->last_meal_time > (unsigned long)p->table->time_to_die)
	{
		pthread_mutex_unlock(&p->meal_lock);
		pthread_mutex_lock(&p->table->table_lock);
		if (!p->table->is_ended)
		{
			p->table->is_ended = 1;
			pthread_mutex_unlock(&p->table->table_lock);
			print_action(p, "died");
		}
		else
			pthread_mutex_unlock(&p->table->table_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->meal_lock);
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*t;
	int		i;

	t = (t_table *) arg;
	while (1)
	{
		pthread_mutex_lock(&t->table_lock);
		if (t->is_ended)
		{
			pthread_mutex_unlock(&t->table_lock);
			break ;
		}
		pthread_mutex_unlock(&t->table_lock);
		i = 0;
		while (i < t->n_philos)
		{
			if (philo_died(&t->philos[i]))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
