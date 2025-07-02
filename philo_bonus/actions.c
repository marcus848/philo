/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:59:36 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 20:34:52 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

void	pick_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->table->death_lock);
	philo->last_meal_time = get_time_in_ms();
	sem_post(philo->table->death_lock);
	print_action(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	philo->meals_eaten++;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pick_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
