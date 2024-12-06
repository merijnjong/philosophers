/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:12:31 by mjong             #+#    #+#             */
/*   Updated: 2024/12/06 15:07:19 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if ((gettimeofday(&time, NULL) == -1) != 0)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		index;
	long	result;
	int		sign;

	index = 0;
	result = 0;
	sign = 1;
	while ((str[index] == ' ' || (str[index] >= 9 && str[index] <= 13)) != 0)
		index++;
	if ((str[index] == '+' || str[index] == '-') != 0)
	{
		if ((str[index] == '-') != 0)
			sign = -1;
		index++;
	}
	while ((str[index] >= '0' && str[index] <= '9') != 0)
	{
		result = result * 10 + (str[index] - '0');
		index++;
	}
	return (sign * result);
}

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->dead_lock);
	if ((*philo->dead == 0) || (msg[0] == 'd') != 0)
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id,
			msg);
		fflush(stdout);
		pthread_mutex_unlock(philo->write_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
}
