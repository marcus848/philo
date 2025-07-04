/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:29:59 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/01 19:17:12 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time_in_ms)
{
	unsigned long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < (unsigned long) time_in_ms)
		usleep(500);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(char **av)
{
	char	*tmp;
	int		i;

	i = 1;
	while (av[i])
	{
		tmp = av[i];
		if (tmp[0] == '+')
			tmp = &av[i][1];
		if (!is_numeric(tmp))
			return (0);
		i++;
	}
	return (1);
}
