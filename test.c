#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main(void)
{
	char *ptr_tiny;
	char *ptr_tiny_1;
	char *ptr_small;
	char *ptr_small_1;
	char *ptr_large;
	char *ptr_lagre_1;

	ptr_tiny = malloc(2);
	ptr_tiny_1 = malloc(128);
	ptr_small = malloc(129);
	ptr_small_1 = malloc(1140);
	ptr_large = malloc(4100);
	ptr_lagre_1 = malloc(80847);
	//printf("ptr = %p\n", (void *)ptr);

	show_alloc_mem();
	//free(ptr);
	return (0);
}
