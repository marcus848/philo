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

	pthread_mutex_lock(&philo->table->write_lock);
	if (!philo->table->is_ended || ft_strcmp(msg, "died") == 0)
	{
		timestamp = get_time_in_ms() - philo->table->start_time;
		printf("%lu Philo %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->table->write_lock);
}
