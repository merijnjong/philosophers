#include "philo.h"

long long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void smart_sleep(long long time)
{
    long long start;

    start = get_time();
    while (get_time() - start < time)
        usleep(100);
}

void print_status(t_data *data, int id, char *status)
{
    pthread_mutex_lock(&data->print_mutex);
    if (!data->someone_died)
        printf("%lld %d %s\n", get_time() - data->start_time, id, status);
    pthread_mutex_unlock(&data->print_mutex);
}
