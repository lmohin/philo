/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 07:38:24 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/29 18:22:09 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		create_threads(t_datas *datas, pthread_t *thread);
int		allocate_philo(t_philo **philo, t_datas *datas, int philo_number);
void	pthread_create_fail(t_datas *datas, pthread_t *thread, int philo_index);

int	manage_threads(t_datas *datas, pthread_t *thread)
{
	int		nbr_philos_created;

	if (datas-> argc == 6 && datas->nbr_of_times_philos_must_eat == 0)
	{
		free(thread);
		free(datas->philos_list);
		return (ALL_GOOD);
	}
	nbr_philos_created = create_threads(datas, thread);
	if (nbr_philos_created == 0)
	{
		free(thread);
		free(datas->philos_list);
		return (SYSTEM_CALL_ERROR);
	}
	check_routine(datas);
	while (nbr_philos_created)
	{
		pthread_join(thread[nbr_philos_created - 1], NULL);
		free((datas->philos_list)[nbr_philos_created - 1]);
		nbr_philos_created--;
	}
	free(thread);
	free(datas->philos_list);
	return (ALL_GOOD);
}

int	create_threads(t_datas *datas, pthread_t *thread)
{
	t_philo	*philo;
	int		philo_index;

	philo_index = 0;
	pthread_mutex_lock(&(datas->mutex_global));
	while (philo_index < datas->nbr_of_philos)
	{
		if (allocate_philo(&philo, datas, philo_index + 1) == SYSTEM_CALL_ERROR)
			return (0);
		(datas->philos_list)[philo_index] = philo;
		(datas->nbr_of_meals)[philo_index] = 0;
		(datas->philos_last_meal)[philo_index] = 0;
		if (pthread_create(thread + philo_index, NULL, &philo_routine, philo))
		{
			pthread_create_fail(datas, thread, philo_index);
			return (0);
		}
		philo_index++;
	}
	datas->start_time = get_the_time(0);
	pthread_mutex_unlock(&(datas->mutex_global));
	return (philo_index);
}

void	pthread_create_fail(t_datas *datas, pthread_t *thread, int philo_index)
{
	ft_putstr_fd("\033[31mphilo: pthread_create error\033[00m\n", 2);
	datas->philos_status = ONE_DEAD;
	pthread_mutex_unlock(&(datas->mutex_global));
	while (philo_index)
	{
		pthread_join(thread[philo_index - 1], NULL);
		free((datas->philos_list)[philo_index]);
		philo_index--;
	}
	free((datas->philos_list)[philo_index]);
}

int	allocate_philo(t_philo **philo, t_datas *datas, int philo_number)
{
	t_philo	*tmp_philo;

	tmp_philo = malloc(sizeof(t_philo));
	if (!tmp_philo)
	{
		ft_putstr_fd("\033[31mphilo: malloc error\033[00m\n", 2);
		while (philo_number)
		{
			free((datas->philos_list)[philo_number - 1]);
			philo_number--;
		}
		return (SYSTEM_CALL_ERROR);
	}
	*philo = tmp_philo;
	(*philo)->philo_number = philo_number;
	(*philo)->datas = datas;
	return (ALL_GOOD);
}
