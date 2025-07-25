/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:18 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 20:17:31 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

// Structs
typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	unsigned long	last_meal_time;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				n_philos;
	int				times_must_eat;
	int				is_ended;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	table_lock;
}	t_table;

t_table	*init_table(int ac, char **av);

// lib
int		ft_atoi(const char *nptr);
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
int		start_threads(t_table *t);

#endif
