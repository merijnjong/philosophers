/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:45:53 by mjong             #+#    #+#             */
/*   Updated: 2024/06/04 14:46:21 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    int             someone_died;
} t_data;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    int             meals_eaten;
    long long       last_meal_time;
    int             left_fork;
    int             right_fork;
    t_data          *data;
} t_philo;

// Utils
long long   get_time(void);
void        smart_sleep(long long time);
void        print_status(t_data *data, int id, char *status);

// Init
int         init_data(t_data *data, int argc, char **argv);
int         init_philos(t_philo **philos, t_data *data);

// Core
void        *philosopher_routine(void *arg);
int         start_simulation(t_philo *philos, t_data *data);

#endif
