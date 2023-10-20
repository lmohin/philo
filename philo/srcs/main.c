/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:24:53 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/17 19:27:51 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_datas	*datas;
	int		return_code;

	datas = malloc(sizeof(t_datas));
	if (!datas)
		return (SYSTEM_CALL_ERROR);
	if (parse_arguments(argc, argv, datas) != ALL_GOOD)
	{
		free(datas);
		return (PARSING_ERROR);
	}
	if (initiate_datas(datas, argc) == SYSTEM_CALL_ERROR)
		return (SYSTEM_CALL_ERROR);
	if (initiate_thread_list(datas) == SYSTEM_CALL_ERROR)
		return_code = SYSTEM_CALL_ERROR;
	else
		return_code = manage_threads(datas, datas->thread);
	destroy_all_mutex(datas, datas->nbr_of_philos);
	free(datas->forks_status);
	free(datas->nbr_of_meals);
	free(datas->philos_last_meal);
	free(datas);
	return (return_code);
}

void	destroy_all_mutex(t_datas *datas, int nbr_of_forks)
{
	int	fork_index;

	fork_index = 0;
	while (fork_index < nbr_of_forks)
	{
		pthread_mutex_destroy(datas->forks + fork_index);
		fork_index++;
	}
	pthread_mutex_destroy(&(datas->mutex_global));
	free(datas->forks);
}
