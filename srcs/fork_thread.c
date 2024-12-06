/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:18:25 by mjong             #+#    #+#             */
/*   Updated: 2024/12/06 15:17:04 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if ((philo->id % 2) != 0)
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

void	take_forks(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	print_message(philo, FORK_TAKEN);
	pthread_mutex_lock(second);
	print_message(philo, FORK_TAKEN);
}

int	create_threads(t_program *program)
{
	int	philo_index;

	philo_index = 0;
	while (philo_index < program->philos[0].num_of_philos)
	{
		if ((pthread_create(&program->philos[philo_index].thread, NULL,
					philo_routine, &program->philos[philo_index])) != 0)
			return (1);
		philo_index++;
	}
	if ((pthread_create(&program->monitor, NULL, check_routine,
				program)) != 0)
		return (1);
	return (0);
}

void	join_threads(t_program *program)
{
	int	philo_index;

	philo_index = 0;
	while (philo_index < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[philo_index].thread, NULL);
		philo_index++;
	}
	pthread_join(program->monitor, NULL);
}
