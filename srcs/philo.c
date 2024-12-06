/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:45:51 by mjong             #+#    #+#             */
/*   Updated: 2024/12/06 13:31:32 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char **argv)
{
	int	arg_index;
	int	char_index;

	if ((argc != 5 && argc != 6) != 0)
		return (1);
	arg_index = 1;
	while (argv[arg_index] != NULL)
	{
		char_index = 0;
		while (argv[arg_index][char_index] != 0)
		{
			if ((argv[arg_index][char_index] < '0'
				|| argv[arg_index][char_index] > '9') != 0)
				return (1);
			char_index++;
		}
		if ((ft_atoi(argv[arg_index]) <= 0) != 0)
			return (1);
		arg_index++;
	}
	return (0);
}

static void	cleanup(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->start_lock);
	free(program->forks);
	free(program->philos);
}

static void	set_simulation_start(t_program *program)
{
	int		i;
	size_t	start_time;

	start_time = get_current_time();
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		program->philos[i].start_time = start_time;
		program->philos[i].last_meal = start_time;
		i++;
	}
	pthread_mutex_lock(&program->start_lock);
	program->start_flag = 1;
	pthread_mutex_unlock(&program->start_lock);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if ((check_args(argc, argv)) != 0)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if ((init_program(&program, argc, argv)) != 0)
		return (1);
	if ((create_threads(&program)) != 0)
		return (1);
	set_simulation_start(&program);
	join_threads(&program);
	cleanup(&program);
	return (0);
}
