/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:27:47 by lmohin            #+#    #+#             */
/*   Updated: 2023/09/04 15:43:50 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo_case(t_datas *datas)
{
	print_action(1, datas, THINKING);
	taking_right_fork(1, datas);
	while (check_philos_status(datas) != ONE_DEAD)
		continue ;
	pthread_mutex_unlock(datas->forks);
}

static void	manage_taking_forks(t_philo *philo)
{
	if (philo->philo_number % 2 == 0)
	{
		taking_left_fork(philo->philo_number, philo->datas);
		taking_right_fork(philo->philo_number, philo->datas);
	}
	else
	{
		taking_right_fork(philo->philo_number, philo->datas);
		taking_left_fork(philo->philo_number, philo->datas);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		wait_time;
	int		nbr_of_meals;

	philo = (t_philo *) arg;
	nbr_of_meals = 0;
	if (philo->datas->nbr_of_philos == 1)
		one_philo_case(philo->datas);
	wait_time = (philo->datas->time_to_eat + philo->datas->time_to_sleep) / 2;
	while (check_philos_status(philo->datas) != ONE_DEAD)
	{
		print_action(philo->philo_number, philo->datas, THINKING);
		if ((philo->datas)->nbr_of_philos % 2 == 1 && nbr_of_meals != 0)
			ft_usleep((philo->datas)->start_time, \
				get_the_time((philo->datas)->start_time), wait_time);
		if (nbr_of_meals == 0 && philo->philo_number % 2 != 1)
			ft_usleep((philo->datas)->start_time, \
				get_the_time((philo->datas)->start_time), \
					(philo->datas)->time_to_eat / 2 + 1);
		manage_taking_forks(philo);
		philo_eating(philo->philo_number, philo->datas);
		nbr_of_meals++;
		print_action(philo->philo_number, philo->datas, SLEEPING);
	}
	return (0);
}
