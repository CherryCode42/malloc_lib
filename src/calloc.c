#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../inc/malloc.h"

void *calloc(size_t nmemb, size_t size)
{
    void *ptr;
    size_t total;

    if (size != 0 && nmemb > SIZE_MAX / size)
        return NULL;

    total = nmemb * size;
    ptr = malloc(total);
    if (!ptr)
        return NULL;

    memset(ptr, 0, total);
    return ptr;
}