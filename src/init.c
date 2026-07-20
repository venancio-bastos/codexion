#include "codexion.h"

int scheduler(char *str)
{
    if (strcmp(str, "fifo") == 0)
        return (0);
    return (1);
}

static int  init_times(t_data *data, char **args)
{
    data->number_of_coders = ft_atol(args[0]);
    data->time_to_burnout = ft_atol(args[1]);
    data->time_to_compile = ft_atol(args[2]);
    data->time_to_debug = ft_atol(args[3]);
    data->time_to_refactor = ft_atol(args[4]);
    data->number_of_compiles_required = ft_atol(args[5]);
    data->dongle_cooldown = ft_atol(args[6]);
    data->scheduler = scheduler(args[7]);
    data->sim_stop = 0;
    data->queue_head = NULL;
    if (data->number_of_coders == -1 || data->time_to_burnout == -1 ||
        data->time_to_compile == -1 || data->time_to_debug == -1 ||
        data->time_to_refactor == -1 || data->number_of_compiles_required == -1 ||
        data->dongle_cooldown == -1)
    {
        data->sim_stop = 1;
        printf("Error: Invalid numeric argument range\n");
        return (1);
    }
    return (0);
}

static int  init_mutexes(t_data *data)
{
    int i;

    data->dongles = ft_calloc(data->number_of_coders, sizeof(pthread_mutex_t));
    if (data->dongles == NULL)
        return (1);
    i = 0;
    while (i < data->number_of_coders)
    {
        pthread_mutex_init(&data->dongles[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->state_mutex, NULL);
    pthread_mutex_init(&data->queue_mutex, NULL);
    return (0);
}

int init_data(t_data *data, char **args)
{
    if (init_times(data, args) == 1)
        return (1);
    if (init_mutexes(data) == 1)
        return (1);
    return (0);
}
