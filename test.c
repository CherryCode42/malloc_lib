#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main(void)
{
	char *ptr;

	ptr = malloc(100);
	printf("ptr = %p\n", (void *)ptr);

	show_alloc_mem();
	//free(ptr);
	return (0);
}
