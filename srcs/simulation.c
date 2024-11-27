/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:12:23 by mjong             #+#    #+#             */
/*   Updated: 2024/11/27 21:16:13 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo->data, philo->id, FORK_TAKEN);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo->data, philo->id, FORK_TAKEN);
	print_status(philo->data, philo->id, EATING);
	philo->last_meal_time = get_time();
	smart_sleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(15000);
	while (!philo->data->someone_died)
	{
		eat(philo);
		if (philo->data->must_eat_count != -1
			&& philo->meals_eaten >= philo->data->must_eat_count)
			break ;
		print_status(philo->data, philo->id, SLEEPING);
		smart_sleep(philo->data->time_to_sleep);
		print_status(philo->data, philo->id, THINKING);
	}
	return (NULL);
}

static int	check_meals(t_philo *philos, t_data *data)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	while (i < data->num_philos)
	{
		if (philos[i].meals_eaten < data->must_eat_count)
			all_ate = 0;
		i++;
	}
	return (all_ate);
}

static int	check_death(t_philo *philos, t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (get_time() - philos[i].last_meal_time > data->time_to_die)
			{
				print_status(data, philos[i].id, DIED);
				data->someone_died = 1;
				return (1);
			}
			i++;
		}
		if (data->must_eat_count != -1 && check_meals(philos, data))
			return (1);
		usleep(1000);
	}
	return (0);
}

int	start_simulation(t_philo *philos, t_data *data)
{
	int i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].last_meal_time = get_time();
		if (pthread_create(&philos[i].thread, NULL,
				philosopher_routine, &philos[i]))
			return (1);
		i++;
	}
	check_death(philos, data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	return (0);
}
