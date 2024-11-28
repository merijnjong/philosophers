/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:12:23 by mjong             #+#    #+#             */
/*   Updated: 2024/11/28 15:20:17 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	return (0);
}

static int	check_values(t_data *data, int argc)
{
	if (data->num_philos < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| (argc == 6 && data->must_eat_count <= 0))
	{
		printf("Error: invalid arguments values\n");
		return (1);
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;
	data->someone_died = 0;
	if (check_values(data, argc))
		return (1);
	return (init_mutex(data));
}

int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = get_time();
		(*philos)[i].data = data;
		if (i == data->num_philos - 1)
		{
			(*philos)[i].left_fork = 0;
			(*philos)[i].right_fork = i;
		}
		else
		{
			(*philos)[i].left_fork = i;
			(*philos)[i].right_fork = i + 1;
		}
		i++;
	}
	return (0);
}
