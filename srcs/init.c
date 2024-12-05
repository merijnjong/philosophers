/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:12:23 by mjong             #+#    #+#             */
/*   Updated: 2024/12/05 12:58:28 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_program *program, int num_philos)
{
	int	i;

	program->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (program->forks == NULL)
		return (1);
	i = 0;
	while (i < num_philos)
	{
		if ((pthread_mutex_init(&program->forks[i], NULL)) != 0)
			return (1);
		i++;
	}
	if ((pthread_mutex_init(&program->write_lock, NULL)) != 0)
		return (1);
	if ((pthread_mutex_init(&program->dead_lock, NULL)) != 0)
		return (1);
	if ((pthread_mutex_init(&program->meal_lock, NULL)) != 0)
		return (1);
	if ((pthread_mutex_init(&program->start_lock, NULL)) != 0)
		return (1);
	program->start_flag = 0;
	return (0);
}

static int	init_philos(t_program *program, char **argv, int num_philos, int i)
{
	while (i < num_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = get_current_time();
		program->philos[i].time_to_die = ft_atoi(argv[2]);
		program->philos[i].time_to_eat = ft_atoi(argv[3]);
		program->philos[i].time_to_sleep = ft_atoi(argv[4]);
		program->philos[i].start_time = get_current_time();
		program->philos[i].num_of_philos = num_philos;
		program->philos[i].num_times_to_eat = -1;
		if (argv[5] != NULL)
			program->philos[i].num_times_to_eat = ft_atoi(argv[5]);
		program->philos[i].dead = &program->dead_flag;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].start_lock = &program->start_lock;
		program->philos[i].program = program;
		i++;
	}
	return (0);
}

static void	assign_forks(t_program *program, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		program->philos[i].l_fork = &program->forks[i];
		if (i == num_philos - 1)
			program->philos[i].r_fork = &program->forks[0];
		else
			program->philos[i].r_fork = &program->forks[i + 1];
		i++;
	}
}

int	init_program(t_program *program, int argc, char **argv)
{
	int	num_philos;

	(void)argc;
	num_philos = ft_atoi(argv[1]);
	if ((num_philos > 200) != 0)
		return (1);
	program->dead_flag = 0;
	if ((init_mutexes(program, num_philos)) != 0)
		return (1);
	program->philos = malloc(sizeof(t_philo) * num_philos);
	if (program->philos == NULL)
		return (1);
	if ((init_philos(program, argv, num_philos, 0)) != 0)
		return (1);
	assign_forks(program, num_philos);
	return (0);
}
