#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "malloc.h"

int main() {
	char *ptr_tiny;
	char *ptr_small;
	char *ptr_large;

	ptr_tiny = malloc(20);
	ptr_small = malloc(400);
	ptr_large = malloc(4100);

	ptr_tiny = realloc(ptr_tiny, 16);
	ptr_tiny = realloc(ptr_tiny, 18);
	ptr_tiny = realloc(ptr_tiny, 450);

	ptr_small = realloc(ptr_small, 300);
	ptr_small = realloc(ptr_small, 400);
	ptr_small = realloc(ptr_small, 4900);

	ptr_large = realloc(ptr_large, 490000);

	show_alloc_mem();
	show_alloc_mem_ex();

	return(0);
}
