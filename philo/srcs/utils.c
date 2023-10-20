/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:09:37 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/29 16:24:59 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int start_time, int time, int time_to_wait)
{
	int	stop_time;

	stop_time = time + time_to_wait;
	while (stop_time - time > 0)
	{
		usleep(100);
		time = get_the_time(start_time);
	}
}

int	get_the_time(int start_time)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time;
	return (time);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

int	ft_positive_atoi(const char	*str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (((str[i] > 8 && str[i] < 14) || str[i] == ' '))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((nbr * 10 + str[i] - '0') / 10 != nbr)
			return (-1);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (str[i])
		return (-1);
	return (nbr);
}
