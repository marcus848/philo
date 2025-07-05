/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:18 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/03 16:09:26 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>

// Structs
typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_time;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	pid_t			*pid;
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_must_eat;
	unsigned long	start_time;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*death_lock;
}	t_table;

t_table	*init_table(int ac, char **av);

// lib
int		ft_atoi(const char *nptr);
int		ft_atol(const char *nptr);
int		ft_strcmp(char *s1, char *s2);

// utils
long	get_time_in_ms(void);
void	ft_usleep(long time_in_ms);
int		check_input(char **av);

// free
void	free_table(t_table *t);

// actions_utils
void	print_action(t_philo *philo, char *msg);
int		single_philo(t_table *t);

// actions
void	*routine(void *arg);

// routine
void	*monitor(void *arg);

// inspector
void	*inspector(void *arg);

// threads
int		start_forks(t_table *t);

#endif
