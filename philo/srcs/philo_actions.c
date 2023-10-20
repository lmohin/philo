/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 22:10:40 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/17 19:31:49 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int philo_number, t_datas *datas, int action)
{
	int	time;

	pthread_mutex_lock(&(datas->mutex_global));
	time = get_the_time(datas->start_time);
	check_if_philo_died(datas, philo_number - 1, time);
	if (datas->philos_status == EVERYONE_ALIVE)
	{
		if (action == EATING)
		{
			printf("%d %d is eating\n", time, philo_number);
			(datas->philos_last_meal)[philo_number - 1] = time;
		}
		else if (action == THINKING)
			printf("%d %d is thinking\n", time, philo_number);
		else if (action == SLEEPING)
			printf("%d %d is sleeping\n", time, philo_number);
		else
			printf("%d %d has taken a fork\n", time, philo_number);
	}
	pthread_mutex_unlock(&(datas->mutex_global));
	if (action == EATING)
		ft_usleep(datas->start_time, time, datas->time_to_eat);
	if (action == SLEEPING)
		ft_usleep(datas->start_time, time, datas->time_to_sleep);
}

void	philo_eating(int philo_number, t_datas *datas)
{
	print_action(philo_number, datas, EATING);
	datas->forks_status[philo_number - 1] = NOT_USED;
	pthread_mutex_unlock(datas->forks + philo_number - 1);
	pthread_mutex_lock(&(datas->mutex_global));
	(datas->nbr_of_meals)[philo_number - 1] += 1;
	pthread_mutex_unlock(&(datas->mutex_global));
	if (datas->nbr_of_philos != 1)
	{
		if (philo_number == 1)
		{
			datas->forks_status[datas->nbr_of_philos - 1] = NOT_USED;
			pthread_mutex_unlock(datas->forks + datas->nbr_of_philos - 1);
		}
		else
		{
			datas->forks_status[philo_number - 2] = NOT_USED;
			pthread_mutex_unlock(datas->forks + philo_number - 2);
		}
	}
}

void	taking_left_fork(int philo_number, t_datas *datas)
{
	if (datas->nbr_of_philos != 1)
	{
		if (philo_number == 1)
		{
			pthread_mutex_lock(datas->forks + datas->nbr_of_philos - 1);
			datas->forks_status[datas->nbr_of_philos - 1] = USED;
		}
		else
		{
			pthread_mutex_lock(datas->forks + philo_number - 2);
			datas->forks_status[philo_number - 2] = USED;
		}
		print_action(philo_number, datas, TAKING_FORK);
	}
}

void	taking_right_fork(int philo_number, t_datas *datas)
{
	pthread_mutex_lock(datas->forks + philo_number - 1);
	datas->forks_status[philo_number - 1] = USED;
	print_action(philo_number, datas, TAKING_FORK);
}
