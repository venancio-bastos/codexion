#include "codexion.h"

static int  check_sim_stop(t_coder *coder)
{
    int stop;

    pthread_mutex_lock(&coder->data->state_mutex);
    stop = coder->data->sim_stop;
    pthread_mutex_unlock(&coder->data->state_mutex);
    return (stop);
}

static void wait_in_queue(t_coder *coder)
{
    pthread_mutex_lock(&coder->data->queue_mutex);
    enqueue_coder(coder->data, coder);
    pthread_mutex_unlock(&coder->data->queue_mutex);
    while (1)
    {
        pthread_mutex_lock(&coder->data->queue_mutex);
        if (coder->data->queue_head == coder)
        {
            pthread_mutex_unlock(&coder->data->queue_mutex);
            break ;
        }
        pthread_mutex_unlock(&coder->data->queue_mutex);
        usleep(500); 
    }
}

static void compile_routine(t_coder *coder)
{
    pthread_mutex_lock(&coder->data->queue_mutex);
    coder->data->queue_head = coder->data->queue_head->next_in_queue;
    pthread_mutex_unlock(&coder->data->queue_mutex);

    pthread_mutex_lock(&coder->data->dongles[coder->left_dongle]);
    print_status(coder, "has taken a dongle");
    pthread_mutex_lock(&coder->data->dongles[coder->right_dongle]);
    print_status(coder, "has taken a dongle");
    
    pthread_mutex_lock(&coder->data->state_mutex);
    coder->last_compile_start = get_current_time();
    pthread_mutex_unlock(&coder->data->state_mutex);
    
    print_status(coder, "is compiling");
    ft_usleep(coder->data->time_to_compile);
    
    pthread_mutex_lock(&coder->data->state_mutex);
    coder->compiles_count++;
    pthread_mutex_unlock(&coder->data->state_mutex);
    
    pthread_mutex_unlock(&coder->data->dongles[coder->left_dongle]);
    pthread_mutex_unlock(&coder->data->dongles[coder->right_dongle]);
}

void    *coder_routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    if (coder->id % 2 == 0)
        usleep(1000);
    while (!check_sim_stop(coder))
    {
        wait_in_queue(coder);
        compile_routine(coder);
        print_status(coder, "is debugging");
        ft_usleep(coder->data->time_to_debug);
        print_status(coder, "is refactoring");
    }
    return (NULL);
}