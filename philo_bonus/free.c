/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:48:11 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 18:54:09 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

void	free_table(t_table *t)
{
	free(t->philos);
	sem_close(t->forks);
	sem_close(t->write_lock);
	sem_close(t->death_lock);
	free(t);
}
