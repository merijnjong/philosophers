/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:18:25 by mjong             #+#    #+#             */
/*   Updated: 2024/12/05 13:11:56 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2)
	{
		*first = philo->l_fork;
		*second = philo->r_fork;
	}
	else
	{
		*first = philo->r_fork;
		*second = philo->l_fork;
	}
}

static void	take_forks(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_message(philo, "has taken a fork");
}

static int	create_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, philo_routine,
				&program->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&program->monitor, NULL, monitor_routine, program))
		return (1);
	return (0);
}

static void	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	pthread_join(program->monitor, NULL);
}
