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

void	print_action(t_philo *philo, char *msg)
{
	unsigned long	timestamp;

	sem_wait(philo->table->write_lock);
	timestamp = get_time_in_ms() - philo->table->start_time;
	printf("%lu Philo %d %s\n", timestamp, philo->id, msg);
	sem_post(philo->table->write_lock);
}

int	single_philo(t_table *t)
{
	pid_t	pid;
	t_philo	*philo;

	philo = &t->philos[0];
	pid = fork();
	if (pid == 0)
	{
		t->start_time = get_time_in_ms();
		sem_wait(t->forks);
		print_action(philo, "take a fork");
		ft_usleep(t->time_to_die);
		print_action(philo, "died");
		free_table(t);
		exit (1);
	}
	return (pid);
}
