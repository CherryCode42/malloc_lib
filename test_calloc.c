#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main(void)
{
    write(1, "before calloc\n", 14);

    char *ptr = calloc(10, sizeof(char));
    if (!ptr)
    {
        write(1, "calloc failed\n", 14);
        return 1;
    }

    write(1, "after calloc\n", 13);

    for (int i = 0; i < 10; i++)
    {
        if (ptr[i] != 0)
        {
            write(1, "not zeroed\n", 11);
            free(ptr);
            return 2;
        }
    }

    free(ptr);
    write(1, "test passed\n", 12);
    return 0;
}
