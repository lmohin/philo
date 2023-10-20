/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:33:14 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/17 19:26:53 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initiate_mutex(t_datas *datas)
{
	int	fork_index;

	datas->forks_status = malloc(sizeof(int) * datas->nbr_of_philos);
	if (!(datas->forks_status))
		return (SYSTEM_CALL_ERROR);
	if (pthread_mutex_init(&(datas->mutex_global), NULL))
	{
		free(datas->forks_status);
		return (SYSTEM_CALL_ERROR);
	}
	fork_index = 0;
	while (fork_index < datas->nbr_of_philos)
	{
		datas->forks_status[fork_index] = NOT_USED;
		datas->philos_last_meal[fork_index] = 0;
		if (pthread_mutex_init(datas->forks + fork_index, NULL))
		{
			destroy_all_mutex(datas, fork_index);
			free(datas->forks_status);
			return (SYSTEM_CALL_ERROR);
		}
		fork_index++;
	}
	return (ALL_GOOD);
}

static int	allocate_datas_components(t_datas *datas)
{
	datas->nbr_of_meals = malloc(sizeof(int) * datas->nbr_of_philos);
	if (!(datas->nbr_of_meals))
		return (SYSTEM_CALL_ERROR);
	datas->forks = malloc(sizeof(pthread_mutex_t) * datas->nbr_of_philos);
	if (!(datas->forks))
	{
		free(datas->nbr_of_meals);
		return (SYSTEM_CALL_ERROR);
	}
	datas->philos_last_meal = malloc(sizeof(int) * datas->nbr_of_philos);
	if (!(datas->philos_last_meal))
	{
		free(datas->nbr_of_meals);
		free(datas->forks);
		return (SYSTEM_CALL_ERROR);
	}
	datas->philos_list = malloc(sizeof(t_philo *) * datas->nbr_of_philos);
	if (!(datas->philos_list))
	{
		free(datas->nbr_of_meals);
		free(datas->forks);
		free(datas->philos_last_meal);
		return (SYSTEM_CALL_ERROR);
	}
	return (ALL_GOOD);
}

int	initiate_datas(t_datas *datas, int argc)
{
	datas->argc = argc;
	datas->philos_status = EVERYONE_ALIVE;
	if (allocate_datas_components(datas) == SYSTEM_CALL_ERROR)
	{
		ft_putstr_fd("\033[31mphilo: malloc error\033[00m\n", 2);
		free(datas);
		return (SYSTEM_CALL_ERROR);
	}
	if (initiate_mutex(datas) == SYSTEM_CALL_ERROR)
	{
		ft_putstr_fd("\033[31mphilo: pthread_mutex_init error\033[00m\n", 2);
		free(datas->philos_last_meal);
		free(datas->nbr_of_meals);
		free(datas->philos_list);
		free(datas);
		return (SYSTEM_CALL_ERROR);
	}
	return (ALL_GOOD);
}

int	parse_arguments(int argc, char **argv, t_datas *datas)
{
	if (argc < 5)
		ft_putstr_fd("\033[31mphilo: not enougth arguments\033[00m\n", 2);
	else if (argc > 6)
		ft_putstr_fd("\033[31mphilo: too much arguments\033[00m\n", 2);
	else
	{
		datas->nbr_of_philos = ft_positive_atoi(argv[1]);
		datas->time_to_die = ft_positive_atoi(argv[2]);
		datas->time_to_eat = ft_positive_atoi(argv[3]);
		datas->time_to_sleep = ft_positive_atoi(argv[4]);
	}
	if (argc < 5 || argc > 6)
		return (PARSING_ERROR);
	if (argc == 6)
		datas->nbr_of_times_philos_must_eat = ft_positive_atoi(argv[5]);
	if (datas->nbr_of_philos <= 0 || datas->time_to_die <= 0 \
		|| datas->time_to_eat <= 0 || datas->time_to_sleep <= 0 \
		|| (argc == 6 && datas->nbr_of_times_philos_must_eat < 0))
	{
		ft_putstr_fd("\033[31mphilo: arguments must be integers between 1", 2);
		ft_putstr_fd("(0 for 5th arg) and -2147483648\033[00m\n", 2);
		return (PARSING_ERROR);
	}
	return (ALL_GOOD);
}

int	initiate_thread_list(t_datas *datas)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * (datas->nbr_of_philos));
	if (!thread)
	{
		free(datas->philos_list);
		ft_putstr_fd("\033[31mphilo: malloc error\033[00m\n", 2);
		return (SYSTEM_CALL_ERROR);
	}
	datas->thread = thread;
	return (ALL_GOOD);
}
