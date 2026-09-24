#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main(void)
{
	char *ptr_tiny;
	char *ptr_tiny_1;
	char *ptr_small;
	char *ptr_large;
	char *ptr_lagre_1;
	int nb = 11;

	ptr_tiny = malloc(2);
	ptr_tiny_1 = malloc(128);
	while (nb > 0) {
		ptr_small = malloc(4095);
		nb--;
	}
	ptr_large = malloc(4100);
	ptr_lagre_1 = malloc(80847);
	//printf("ptr = %p\n", (void *)ptr);

	show_alloc_mem();
	free(ptr_tiny);
	free(ptr_tiny_1);
	free(ptr_large);
	free(ptr_lagre_1);
	while (nb < 11) {
		ptr_small = malloc(4095);
		nb++;
	}
	return (0);
}
