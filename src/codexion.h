#ifndef CODEXION_H_
# define CODEXION_H_

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
    int             number_of_coders;
    long long       time_to_burnout;
    long long       time_to_compile;
    long long       time_to_debug;
    long long       time_to_refactor;
    int             number_of_compiles_required;
    long long       dongle_cooldown;
    int             scheduler;
    int             sim_stop;
    long long       start_time;
    pthread_mutex_t state_mutex;
    pthread_mutex_t *dongles;
    pthread_mutex_t print_mutex;
    struct s_coder  *queue_head;
    pthread_mutex_t queue_mutex;
}   t_data;

typedef struct s_coder
{
    int             id;
    int             compiles_count;
    pthread_t       thread_id;
    long long       last_compile_start;
    int             left_dongle;
    int             right_dongle;
    t_data          *data;
    struct s_coder  *next_in_queue;
}   t_coder;

int         scheduler_type(char *str);
int         is_numeric(char *str);
int         check_args(char **args);

int         scheduler(char *str);
int         init_data(t_data *data, char **args);

void        *ft_calloc(size_t count, size_t size);
long long   ft_atol(char *str);
long long   get_current_time(void);
void        ft_usleep(long long time_in_ms);
void        print_status(t_coder *coder, char *status);

void        enqueue_coder(t_data *data, t_coder *new_coder);

void        *coder_routine(void *arg);

void        *monitor_routine(void *arg);

#endif