/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:07:25 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 20:10:06 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/types.h>

void	print_action(t_philo *philo, char *msg)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->table->write_lock);
	if (!philo->table->is_ended || ft_strcmp(msg, "died") == 0)
	{
		timestamp = get_time_in_ms() - philo->table->start_time;
		printf("%lu Philo %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die);
	print_action(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	single_philo(t_table *t)
{
	t_philo	*philo;

	philo = &t->philos[0];
	t->start_time = get_time_in_ms();
	philo->last_meal_time = t->start_time;
	pthread_create(&philo->thread_id, NULL, &routine_one_philo, philo);
	pthread_join(philo->thread_id, NULL);
	return (0);
}
