#include <stdio.h>
#include "inc/malloc.h"

int main(void)
{
    printf("t_block = %zu bytes\n", sizeof(t_block));
    printf("t_zone = %zu bytes\n", sizeof(t_zone));
    return (0);
}