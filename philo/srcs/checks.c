/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:29:49 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/29 13:59:53 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_if_someone_died(t_datas *datas);
void	check_everyone_nbr_meals(t_datas *datas);

int	check_philos_status(t_datas *datas)
{
	pthread_mutex_lock(&(datas->mutex_global));
	if (datas->philos_status == ONE_DEAD)
	{
		pthread_mutex_unlock(&(datas->mutex_global));
		return (ONE_DEAD);
	}
	pthread_mutex_unlock(&(datas->mutex_global));
	return (EVERYONE_ALIVE);
}

void	check_routine(t_datas *datas)
{
	while (check_philos_status(datas) == EVERYONE_ALIVE)
	{
		check_if_someone_died(datas);
		if (datas->argc == 6)
			check_everyone_nbr_meals(datas);
		usleep(800);
	}
}

void	check_if_someone_died(t_datas *datas)
{
	int	philo_index;
	int	time;

	philo_index = 0;
	while (philo_index < datas->nbr_of_philos)
	{
		pthread_mutex_lock(&(datas->mutex_global));
		time = get_the_time(datas->start_time);
		check_if_philo_died(datas, philo_index, time);
		pthread_mutex_unlock(&(datas->mutex_global));
		philo_index++;
	}
}

void	check_if_philo_died(t_datas *datas, int philo_index, int time)
{
	if (time - datas->philos_last_meal[philo_index] >= datas->time_to_die \
		&& datas->philos_status == EVERYONE_ALIVE)
	{
		printf("%d %d died\n", time, philo_index + 1);
		datas->philos_status = ONE_DEAD;
	}
}

void	check_everyone_nbr_meals(t_datas *datas)
{
	int	philo_index;
	int	stop;
	int	nbr_of_meals;

	stop = 0;
	philo_index = 0;
	while (philo_index < datas->nbr_of_philos && !stop)
	{
		pthread_mutex_lock(&(datas->mutex_global));
		nbr_of_meals = (datas->nbr_of_meals)[philo_index];
		pthread_mutex_unlock(&(datas->mutex_global));
		if (nbr_of_meals < datas->nbr_of_times_philos_must_eat)
			stop = 1;
		philo_index++;
	}
	pthread_mutex_lock(&(datas->mutex_global));
	if (!stop)
		datas->philos_status = ONE_DEAD;
	pthread_mutex_unlock(&(datas->mutex_global));
}
