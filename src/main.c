#include "codexion.h"

int scheduler_type(char *str)
{
    if (strcmp(str, "fifo") != 0 && strcmp(str, "edf") != 0)
    {
        printf("Error: Scheduler must be 'fifo' or 'edf'\n");
        return (0);
    }
    return (1);
}

int is_numeric(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+')
        i++;
    
    if (str[i] == '\0')
        return (0);

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int check_args(char **args)
{
    int i;

    i = 0;
    while (i < 7)
    {
        if (!is_numeric(args[i]))
        {
            printf("Error: Invalid numeric argument at position %d\n", i + 1);
            return (0);
        }
        i++;
    }
    if (!scheduler_type(args[7]))
        return (0);
    return (1);
}

int main(int ac, char **av)
{
    t_data  data;
    int     i;
    
    if (ac != 9)
    {
        printf("Error: Invalid number of arguments\n");
        return (1);
    }
    
    if (!check_args(av + 1))
        return (1);

    init_data(&data, av + 1);

    i = 0;
    return (0);
}