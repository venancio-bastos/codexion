#include "codexion.h"

void init_data(t_data *data, char **args)
{
    data->number_of_coders = atoi(args[0]);
    data->time_to_burnout = atoi(args[1]);
    data->time_to_compile = atoi(args[2]);
    data->time_to_debug = atoi(args[3]);
    data->time_to_refactor = atoi(args[4]);
    data->number_of_compiles_required = atoi(args[5]);
    data->dongle_cooldown = atoi(args[6]);
    
    if (strcmp(args[7], "fifo") == 0)
        data->scheduler = 0;
    else
        data->scheduler = 1;

    data->is_running = 1;


    data->coders = calloc(sizeof(t_coder) * data->number_of_coders);
    data->dongles = calloc(sizeof(t_dongle) * data->number_of_coders);


    if (!data->coders || !data->dongles)
        printf("ERROR: Not able to allocate memory!\n");
}