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

void	start_philo_process(t_philo *philo)
{
	// pthread_create(&philo->monitor_thread, NULL, &monitor, philo);
	routine(philo);
	// pthread_join(philo->monitor_thread, NULL);
}

void	kill_all_processes(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		kill(t->philos[i].pid, SIGKILL);
		i++;
	}
}

void	wait_and_watch(t_table *t)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < t->n_philos)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0)
		{
			kill_all_processes(t);
			return ;
		}
		sem_wait(t->satisfied);
		i++;
	}
	// todos comeram o suficiente
	kill_all_processes(t);
}

int	create_philo_fork(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		t->philos[i].pid = fork();
		if (t->philos[i].pid < 0)
		{
			printf("[ERROR] fork failed\n");
			return (1);
		}
		if (t->philos[i].pid == 0)
		{
			start_philo_process(&t->philos[i]);
			exit (0);
		}
		i++;
	}
	return (0);
}


int	start_forks(t_table *t)
{
	t->start_time = get_time_in_ms();
	if (create_philo_fork(t))
		return (1);
	return (0);
}
