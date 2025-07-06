/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:23:11 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/03 16:10:46 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/types.h>

void	set_args(t_table *t, int ac, char **av)
{
	t->n_philos = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	t->times_must_eat = -1;
	if (ac == 6)
		t->times_must_eat = ft_atoi(av[5]);
	t->start_time = get_time_in_ms();
	sem_unlink("/write_lock");
	sem_unlink("/death_lock");
	sem_unlink("/forks");
	t->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	t->death_lock = sem_open("/death_lock", O_CREAT, 0644, 1);
	t->forks = sem_open("/forks", O_CREAT, 0644, t->n_philos);
	if (t->write_lock == SEM_FAILED || t->death_lock == SEM_FAILED
		|| t->forks == SEM_FAILED)
	{
		printf("[ERROR] Create Semaphores\n");
		exit (1);
	}
}

int	alloc_table(t_table *t)
{
       t->philos = malloc(sizeof(t_philo) * t->n_philos);
       if (!t->philos)
               return (1);
       t->pid = malloc(sizeof(pid_t) * t->n_philos);
       if (!t->pid)
               return (1);
       return (0);
}

int	init_philos(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		t->philos[i].id = i + 1;
		t->philos[i].meals_eaten = t->times_must_eat;
		t->philos[i].last_meal_time = t->start_time;
		t->philos[i].table = t;
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
	if (init_philos(t))
	{
		free_table(t);
		return (NULL);
	}
	return (t);
}
