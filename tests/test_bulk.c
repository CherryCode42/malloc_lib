#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main(void)
{
	char *ptr;
	char *ptr_1;
	char *ptr_2;
	char *ptr_3;
	char *ptr_4;
	char *ptr_5;


	ptr = malloc(2);
	ptr_1 = malloc(127);

	ptr_2 = malloc(129);
	ptr_3 = malloc(128);

	strcpy(ptr, "0");
	strcpy(ptr_1, "Hello!");
	strcpy(ptr_2, "I'm Irina");
	strcpy(ptr_3, "Arefeva");
	
	show_alloc_mem_ex("DUMP");
	free(ptr);
	free(ptr_1);
	free(ptr_2);
	free(ptr_3);
	show_alloc_mem_ex("HISTORY");
	return (0);
}
