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

void	pick_forks(t_philo *philo)
{
	unsigned long	death_time;

	death_time = (unsigned long) philo->table->time_to_die;
	sem_wait(philo->table->death_lock);
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	if (get_time_in_ms() - philo->last_meal_time > death_time)
	{
		print_action(philo, "died");
		free_table(philo->table);
		exit (EXIT_FAILURE);
	}
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	sem_post(philo->table->death_lock);
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
	unsigned long	death_time;
	t_philo			*philo;

	philo = (t_philo *) arg;
	death_time = (unsigned long) philo->table->time_to_die;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (philo->meals_eaten != 0)
	{
		pick_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
	// sem_close(philo->table->forks);
	// sem_close(philo->table->write_lock);
	// sem_close(philo->table->death_lock);
	free_table(philo->table);
	exit (1);
	return (NULL);
}
