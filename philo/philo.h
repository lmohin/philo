/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:28:46 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/17 19:28:13 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define EATING 0
# define SLEEPING 1
# define TAKING_FORK 2
# define THINKING 3

# define ALL_GOOD 0
# define PARSING_ERROR 1
# define SYSTEM_CALL_ERROR 2

# define EVERYONE_ALIVE 0
# define ONE_DEAD 1

# define NOT_USED 0
# define USED 1

int		get_the_time(int start_time);
int		ft_positive_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_usleep(int start_time, int time, int time_to_wait);

typedef struct s_philo	t_philo;

typedef struct s_datas
{
	int				argc;
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_times_philos_must_eat;
	int				start_time;
	int				philos_status;
	pthread_mutex_t	mutex_global;
	pthread_mutex_t	*forks;
	pthread_t		*thread;
	int				*philos_last_meal;
	int				*nbr_of_meals;
	t_philo			**philos_list;
	int				*forks_status;
}	t_datas;

typedef struct s_philo
{
	int		philo_number;
	t_datas	*datas;
}	t_philo;

void	destroy_all_mutex(t_datas *datas, int nbr_of_mutex);

int		initiate_datas(t_datas *datas, int argc);
int		parse_arguments(int argc, char **argv, t_datas *datas);
int		initiate_thread_list(t_datas *datas);
int		manage_threads(t_datas *datas, pthread_t *thread);

void	print_action(int philo_number, t_datas *datas, int action);
void	philo_eating(int philo_number, t_datas *datas);
void	taking_right_fork(int philo_number, t_datas *datas);
void	taking_left_fork(int philo_number, t_datas *datas);
void	*philo_routine(void *arg);

int		check_philos_last_meal(t_datas *datas);
void	check_nbr_times_eating(t_datas *datas);
int		check_philos_status(t_datas *datas);
void	check_if_philo_died(t_datas *datas, int philo_index, int time);
void	check_routine(t_datas *datas);
#endif
