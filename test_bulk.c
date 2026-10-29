#include <stdio.h>
#include <stdlib.h>
#include "inc/malloc.h"

int main(void)
{
	char *ptr;
	char *ptr_1;
	

	ptr = malloc(2);
	ptr_1 = malloc(127);

	strcpy(ptr, "0");
	strcpy(ptr_1, "Hello world!");
	

	show_alloc_mem_ex("HISTORY");
	free(ptr);
	free(ptr_1);
	free(ptr_2);
	free(ptr_3);

	return (0);
}
