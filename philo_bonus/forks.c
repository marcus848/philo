/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:47:57 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/03 16:40:35 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>
#include <sys/types.h>

int		create_philo_fork(t_table *t, int id);
void	kill_all_processes(t_table *t);

void	take_process(t_table *t)
{
	int	i;
	int	status;

	i = -1;
	while (i++ < t->n_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == EXIT_FAILURE)
				return (kill_all_processes(t));
	}
}

int	start_philo_process(t_table *t)
{
	int	i;

	t->start_time = get_time_in_ms();
	i = -1;
	while (++i < t->n_philos)
	{
		create_philo_fork(t, i);
		usleep(1);
	}
	take_process(t);
	return (0);
}

void	kill_all_processes(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		kill(t->pid[i], SIGKILL);
		i++;
	}
}

int	create_philo_fork(t_table *t, int id)
{
	pid_t	pid;
	t_philo	*philo;

	pid = fork();
	if (pid == 0)
	{
		philo = &t->philos[id];
		if (philo->id % 2 == 0)
			usleep(500);
		routine(philo);
		sem_close(t->write_lock);
		sem_close(t->forks);
		free_table(t);
		exit (1);
	}
	else
		t->pid[id] = pid;
	return (0);
}

int	start_forks(t_table *t)
{
	pid_t	pid;
	int	status;

	t->start_time = get_time_in_ms();
	if (t->n_philos == 1)
	{
		pid = single_philo(t);
		waitpid(pid, &status, 0);
	}
	else if (start_philo_process(t))
		return (1);
	return (0);
}
