/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:45:51 by mjong             #+#    #+#             */
/*   Updated: 2024/06/04 14:46:39 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    t_philo *philos;

    if (argc != 5 && argc != 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }

    if (init_data(&data, argc, argv))
        return (1);

    philos = malloc(sizeof(t_philo) * data.num_philos);
    if (!philos)
        return (1);

    if (init_philos(&philos, &data))
    {
        free(philos);
        return (1);
    }

    if (start_simulation(philos, &data))
    {
        // Cleanup
        free(philos);
        return (1);
    }

    free(philos);
    return (0);
}
