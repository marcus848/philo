/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:59:36 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/03 16:38:43 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_life(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	unsigned long	now;

	while (1)
	{
		usleep(500); // Checagem precisa sem sobrecarregar
		sem_wait(philo->table->death_lock);
		now = get_time_in_ms();
		if (now - philo->last_meal_time > (unsigned long)philo->table->time_to_die)
		{
			print_action(philo, "died");
			sem_post(philo->table->death_lock);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->table->death_lock);
	}
	return (NULL);
}

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
	philo->meals_eaten--;
	ft_usleep(philo->table->time_to_eat);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	pthread_t	monitor;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_create(&monitor, NULL, &monitor_life, philo);
	while (philo->meals_eaten != 0)
	{
		pick_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
	exit (1);
	return (NULL);
}
