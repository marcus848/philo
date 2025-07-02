/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:47:57 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 20:19:14 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_create(&t->philos[i].thread_id,
				NULL, &routine, &t->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	start_monitors(t_table *t, pthread_t *mon, pthread_t *insp)
{
	if (pthread_create(mon, NULL, &monitor, t) != 0)
		return (1);
	if (t->times_must_eat > 0)
		if (pthread_create(insp, NULL, &inspector, t) != 0)
			return (1);
	return (0);
}

void	join_threads(t_table *t, pthread_t mon, pthread_t insp)
{
	int	i;

	pthread_join(mon, NULL);
	if (t->times_must_eat > 0)
		pthread_join(insp, NULL);
	i = 0;
	while (i < t->n_philos)
	{
		pthread_join(t->philos[i].thread_id, NULL);
		i++;
	}
}

int	start_threads(t_table *t)
{
	pthread_t	mon;
	pthread_t	insp;

	t->start_time = get_time_in_ms();
	if (create_philo_threads(t))
		return (1);
	if (start_monitors(t, &mon, &insp))
		return (1);
	join_threads(t, mon, insp);
	return (0);
}
