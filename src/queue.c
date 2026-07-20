#include "codexion.h"

static void insert_edf(t_data *data, t_coder *new_coder)
{
    t_coder *curr;

    if (new_coder->last_compile_start < data->queue_head->last_compile_start)
    {
        new_coder->next_in_queue = data->queue_head;
        data->queue_head = new_coder;
    }
    else
    {
        curr = data->queue_head;
        while (curr->next_in_queue != NULL &&
            curr->next_in_queue->last_compile_start <=
            new_coder->last_compile_start)
        {
            curr = curr->next_in_queue;
        }
        new_coder->next_in_queue = curr->next_in_queue;
        curr->next_in_queue = new_coder;
    }
}

void    enqueue_coder(t_data *data, t_coder *new_coder)
{
    t_coder *curr;

    new_coder->next_in_queue = NULL;
    if (data->queue_head == NULL)
    {
        data->queue_head = new_coder;
        return ;
    }
    if (data->scheduler == 0)
    {
        curr = data->queue_head;
        while (curr->next_in_queue != NULL)
            curr = curr->next_in_queue;
        curr->next_in_queue = new_coder;
    }
    else
        insert_edf(data, new_coder);
}