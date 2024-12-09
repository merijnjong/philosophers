/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:45:53 by mjong             #+#    #+#             */
/*   Updated: 2024/12/06 15:16:43 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define MIN_TIME 60

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	int					meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	int					num_of_philos;
	int					num_times_to_eat;
	int					*dead;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	pthread_mutex_t		*start_lock;
	struct s_program	*program;
}	t_philo;

typedef struct s_program
{
	int					dead_flag;
	int					start_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		start_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	pthread_t			monitor;
}	t_program;

// check.c
void	wait_for_start(t_philo *philo);
int		check_death(t_philo *philo);
int		check_philos(t_program *program);
int		can_continue(t_philo *philo);

// dining_actions.c
int		check_meals(t_program *program);
void	philo_eat(t_philo *philo);

// fork_thread.c
void	join_threads(t_program *program);
int		create_threads(t_program *program);
void	take_forks(t_philo *philo, pthread_mutex_t *first,
			pthread_mutex_t *second);
void	get_forks(t_philo *philo, pthread_mutex_t **first,
			pthread_mutex_t **second);

// init.c
int		init_program(t_program *program, int argc, char **argv);

//philo_actions.c
void	*check_routine(void *arg);
void	*philo_routine(void *arg);

// philo_utils.c
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		ft_atoi(const char *str);
void	print_message(t_philo *philo, char *msg);

#endif
