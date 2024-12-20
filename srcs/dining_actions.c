/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:01:45 by mjong             #+#    #+#             */
/*   Updated: 2024/12/12 13:14:39 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->eating = 1;
	print_message(philo, EATING);
	pthread_mutex_unlock(philo->meal_lock);
}

static void	finish_eating(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_forks(philo, &first_fork, &second_fork);
	take_forks(philo, first_fork, second_fork);
	start_eating(philo);
	ft_usleep2(philo, philo->time_to_eat);
	finish_eating(philo, first_fork, second_fork);
}

int	check_meals(t_program *p)
{
	int	index;
	int	finished;

	if ((p->philos[0].num_times_to_eat == -1) != 0)
		return (0);
	index = 0;
	finished = 0;
	while (index < p->philos[0].num_of_philos)
	{
		pthread_mutex_lock(&p->meal_lock);
		if ((p->philos[index].meals_eaten
				>= p->philos[index].num_times_to_eat) != 0)
			finished++;
		pthread_mutex_unlock(&p->meal_lock);
		index++;
	}
	return (finished == p->philos[0].num_of_philos);
}
