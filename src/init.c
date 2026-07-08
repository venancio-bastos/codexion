#include "codexion.h"

void    init_data(char **args)
{
    int i;

    i = 0;
    while (args[i] != NULL)
    {
        printf("%s\n", args[i]);
        i++;
    }
}