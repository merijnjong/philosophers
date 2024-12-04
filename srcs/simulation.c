/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:12:23 by mjong             #+#    #+#             */
/*   Updated: 2024/12/04 14:15:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo->data, philo->id, FORK_TAKEN);
		while (!check_death(philo))
			usleep(100);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return;
	}

	if (philo->id % 2 == 0)
		usleep(1000);
	
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo->data, philo->id, FORK_TAKEN);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo->data, philo->id, FORK_TAKEN);
	
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	print_status(philo->data, philo->id, EATING);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	
	smart_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(15000);
	while (!check_death(philo))
	{
		eat(philo);
		pthread_mutex_lock(&philo->data->meal_mutex);
		if (philo->data->must_eat_count != -1 && 
			philo->meals_eaten >= philo->data->must_eat_count)
		{
			pthread_mutex_unlock(&philo->data->meal_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->meal_mutex);
		if (philo->data->num_philos > 1)
		{
			print_status(philo->data, philo->id, SLEEPING);
			smart_sleep(philo->data->time_to_sleep);
			print_status(philo->data, philo->id, THINKING);
		}
	}
	return (NULL);
}

static void	monitor_philos(t_philo *philos, t_data *data)
{
	int	i;
	int	all_ate;
	long long current_time;
	long long last_meal;

	while (1)
	{
		i = -1;
		all_ate = 1;
		while (++i < data->num_philos)
		{
			pthread_mutex_lock(&data->meal_mutex);
			current_time = get_time();
			last_meal = philos[i].last_meal_time;
			if (current_time - last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->someone_died = 1;
				print_status(data, philos[i].id, DIED);
				pthread_mutex_unlock(&data->death_mutex);
				pthread_mutex_unlock(&data->meal_mutex);
				return;
			}
			if (data->must_eat_count != -1)
			{
				if (philos[i].meals_eaten < data->must_eat_count)
					all_ate = 0;
			}
			pthread_mutex_unlock(&data->meal_mutex);
			usleep(100);
		}
		if (data->must_eat_count != -1 && all_ate)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->all_ate = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return;
		}
	}
}

int	start_simulation(t_philo *philos, t_data *data)
{
	int	i;

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
	monitor_philos(philos, data);
	i = 0;
	while (i < data->num_philos)
		pthread_join(philos[i++].thread, NULL);
	clean_up(data, philos);
	return (0);
}
