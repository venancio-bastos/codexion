#include "codexion.h"

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;

    ptr = malloc(count * size);
    
    if (!ptr)
        return (NULL);
        
    memset(ptr, 0, count * size);
    
    return (ptr);
}

long long   ft_atol(char *str)
{
    int         i;
    long long   result;

    i = 0;
    result = 0;

    if (str[i] == '+')
        i++;

    while (str[i] != '\0')
    {
        result = (result * 10) + (str[i] - '0');

        if (result > INT_MAX)
            return (-1);
        i++;
    }
    return (result);
}

long long   get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        return (-1);

    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
void    ft_usleep(long long time_in_ms)
{
    long long   start_time;

    start_time = get_current_time();

    while ((get_current_time() - start_time) < time_in_ms)
        usleep(500);
}
void print_status(t_coder *coder, char *status)
{
    pthread_mutex_lock(&coder->data->state_mutex);
    if (coder->data->sim_stop == 0)
    {
        pthread_mutex_lock(&coder->data->print_mutex);
        printf("%lld %d %s\n", get_current_time() - coder->data->start_time, coder->id, status);
        pthread_mutex_unlock(&coder->data->print_mutex);
    }
    pthread_mutex_unlock(&coder->data->state_mutex);
}
