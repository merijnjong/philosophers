/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:06:16 by mjong             #+#    #+#             */
/*   Updated: 2024/12/12 15:07:09 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, FORK_TAKEN);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->r_fork);
}

static void	philo_cycle(t_philo *philo)
{
	print_message(philo, THINKING);
	ft_usleep(1);
	philo_eat(philo);
	if (philo->meals_eaten != philo->num_times_to_eat)
	{
		print_message(philo, SLEEPING);
		ft_usleep2(philo, philo->time_to_sleep);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_start(philo);
	if (philo->num_of_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	init_philo_state(philo);
	while (can_continue(philo) != 0)
		philo_cycle(philo);
	return (NULL);
}

void	*check_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	wait_for_start(&program->philos[0]);
	while (1)
	{
		if (check_philos(program) != 0)
			return (NULL);
		if (check_meals(program) != 0)
			return (NULL);
		usleep(50);
	}
	return (NULL);
}
