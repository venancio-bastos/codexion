#ifndef CODEXION_H_
# define CODEXION_H_

# include <stdio.h>
#include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_dongle
{
    int             id;
    long long       next_available_time;
    pthread_mutex_t mutex;
}           t_dongle;

typedef struct s_coder
{
    int             id;
    pthread_t       thread_id;
    int             compile_count;
    long long       last_compile;
    struct s_dongle *left_dongle;
    struct s_dongle *right_dongle;
    struct s_data   *data;
    pthread_mutex_t coder_mutex;
    
}           t_coder;

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
    long long       start_time;
    int             is_running;
    t_coder         *coders;
    t_dongle        *dongles;
    pthread_mutex_t print_mutex;
    pthread_mutex_t data_mutex;
}           t_data;

int     scheduler_type(char *str);
int     is_numeric(char *str);
int     check_args(char **args);

void    init_data(t_data *data, char **args);

void    *ft_calloc(size_t count, size_t size);

#endif