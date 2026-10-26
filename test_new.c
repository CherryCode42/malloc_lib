#include <stdlib.h>


#define COUNT 100000

int main(void)
{
    void *ptrs[COUNT];
    int i;

    i = 0;
    while (i < COUNT)
    {
        ptrs[i] = malloc(128);
        if (!ptrs[i])
            return (1);
        ((char *)ptrs[i])[0] = 1;
        i++;
    }

    i = 0;
    while (i < COUNT)
    {
        free(ptrs[i]);
        i++;
    }

    return (0);
}