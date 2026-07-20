#include "codexion.h"

static int  check_burnout(t_coder *coder)
{
    long long   time_passed;

    pthread_mutex_lock(&coder->data->state_mutex);
    time_passed = get_current_time() - coder->last_compile_start;
    if (time_passed > coder->data->time_to_burnout)
    {
        coder->data->sim_stop = 1;
        pthread_mutex_lock(&coder->data->print_mutex);
        printf("%lld %d burnout\n", get_current_time() - coder->data->start_time, coder->id);
        pthread_mutex_unlock(&coder->data->print_mutex);
        pthread_mutex_unlock(&coder->data->state_mutex);
        return (1);
    }
    pthread_mutex_unlock(&coder->data->state_mutex);
    return (0);
}

static int  check_all_finished(t_coder *coders)
{
    int i;
    int finished;
    int req;

    i = 0;
    finished = 0;
    req = coders[0].data->number_of_compiles_required;
    if (req == -1)
        return (0);
    while (i < coders[0].data->number_of_coders)
    {
        pthread_mutex_lock(&coders[0].data->state_mutex);
        if (coders[i].compiles_count >= req)
            finished++;
        pthread_mutex_unlock(&coders[0].data->state_mutex);
        i++;
    }
    if (finished == coders[0].data->number_of_coders)
    {
        pthread_mutex_lock(&coders[0].data->state_mutex);
        coders[0].data->sim_stop = 1;
        pthread_mutex_unlock(&coders[0].data->state_mutex);
        return (1);
    }
    return (0);
}

void    *monitor_routine(void *arg)
{
    t_coder *coders;
    int     i;

    coders = (t_coder *)arg;
    while (1)
    {
        i = 0;
        while (i < coders[0].data->number_of_coders)
        {
            if (check_burnout(&coders[i]))
                return (NULL);
            i++;
        }
        if (check_all_finished(coders))
            return (NULL);

        usleep(1000); 
    }
    return (NULL);
}