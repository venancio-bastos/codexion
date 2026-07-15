#include "codexion.h"

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;

    ptr = malloc(count * size);
    
    if (!ptr)
        return (NULL);
        
    memset(ptr, 0, count * size);
    
    return (ptr);
}