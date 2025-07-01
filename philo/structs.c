/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:23:11 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 20:10:06 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	set_args(t_table *t, int ac, char **av)
{
	t->n_philos = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	t->times_must_eat = -1;
	if (ac == 6)
		t->times_must_eat = ft_atoi(av[5]);
	t->is_ended = 0;
	t->start_time = get_time_in_ms();
	pthread_mutex_init(&t->write_lock, NULL);
	pthread_mutex_init(&t->table_lock, NULL);
}

int	alloc_table(t_table *t)
{
	t->forks = malloc(sizeof(pthread_mutex_t) * t->n_philos);
	if (!t->forks)
		return (1);
	t->philos = malloc(sizeof(t_philo) * t->n_philos);
	if (!t->philos)
	{
		free(t->forks);
		return (1);
	}
	return (0);
}

int	init_forks(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_mutex_init(&t->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_philos(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		t->philos[i].id = i + 1;
		t->philos[i].meals_eaten = 0;
		t->philos[i].last_meal_time = t->start_time;
		t->philos[i].left_fork = &t->forks[i];
		t->philos[i].right_fork = &t->forks[(i + 1) % t->n_philos];
		t->philos[i].table = t;
		if (pthread_mutex_init(&t->philos[i].meal_lock, NULL))
			return (1);
		i++;
	}
	return (0);
}

t_table	*init_table(int ac, char **av)
{
	t_table	*t;

	t = malloc(sizeof(t_table));
	if (!t)
		return (NULL);
	set_args(t, ac, av);
	if (alloc_table(t))
	{
		free(t);
		return (NULL);
	}
	if (init_forks(t) || init_philos(t))
	{
		free_table(t);
		return (NULL);
	}
	return (t);
}
