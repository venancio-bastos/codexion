#include "codexion.h"

int scheduler_type(char *str)
{
    if (!(strcmp("fifo", str) == 0 || strcmp("edf", str) == 0))
    {
        printf("ERROR: Scheduler must be fifo or edf.");
        return (1);
    }
    return (0);
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

int check_args(int ac, char **av)
{
    int i;
    if (ac < 8)
    {
        printf("ERROR: Missing arguments.");
        return (1);
    }

    i = 0;
    while (i < 7)
    {
        if (!is_numeric(av[i]))
        {
            printf("ERROR: An arg its not an integer.");
            return (0);
        }
        if (i == 0)
        {
            if (av[i] < 1)
            {
                printf("ERROR: Must have at least 1 coder.");
            }
        }
        i++;
    }

    if (!scheduler_type(av[i]))
        return (0);
    return (1);
}

int main(int ac, char **av)
{
    if (!check_args(ac, av + 1))
        return (1);

    
    return (0);
}