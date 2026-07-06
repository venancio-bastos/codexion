#include <stdio.h>

int check_args(int ac, char **av)
{
    if (ac != 9)
    {
        printf("ERROR: Missing arguments");
        return (1);
    }
    
    return (0);
}

int main(int ac, char **av)
{
        
    if (check_args(ac, **av) != 0)
        return (1);

    

    return (0);
}