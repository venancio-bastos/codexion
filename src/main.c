#include "codexion.h"

static int  start_simulation(t_data *data, t_coder *coders)
{
    int         i;
    pthread_t   monitor;

    data->start_time = get_current_time();
    i = 0;
    while (i < data->number_of_coders)
    {
        coders[i].id = i + 1;
        coders[i].left_dongle = coders[i].id - 1;
        coders[i].right_dongle = coders[i].id % data->number_of_coders;
        coders[i].data = data;
        coders[i].last_compile_start = data->start_time;
        pthread_create(&coders[i].thread_id, NULL, coder_routine, &coders[i]);
        i++;
    }
    pthread_create(&monitor, NULL, monitor_routine, coders);
    pthread_join(monitor, NULL);
    i = -1;
    while (++i < data->number_of_coders)
        pthread_join(coders[i].thread_id, NULL);
    return (0);
}

int main(int ac, char **av)
{
    t_data      data;
    t_coder     *coders;

    if (ac != 9)
    {
        printf("Error: Invalid number of arguments\n");
        return (1);
    }
    if (!check_args(av + 1) || init_data(&data, av + 1) == 1)
        return (1);
    coders = ft_calloc(data.number_of_coders, sizeof(t_coder));
    if (!coders)
        return (1);
    start_simulation(&data, coders);
    free(data.dongles);
    free(coders);
    return (0);
}