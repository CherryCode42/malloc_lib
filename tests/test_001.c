#include <stdio.h>
#include <stdlib.h>
// #include "libft.h"

int main( int argc, char* argv[] ) {
	(void)argc;
	(void)argv;

	// printf("App begin\n\n");
	// char* ptr = malloc(1024);
	// printf("ptr = %p\n", ptr);
	// printf("\nApp end\n");

	// int i = 0;
	// while (i < 1024)
	// {
	// 	ptr = (char*)malloc(102);
	// 	ptr[0] = 42;
	// 	printf("ptr = %p\n", ptr);
	// 	// free(addr);
	// 	i++;
	// }

	printf("TEST 1:\n");
	void *a = malloc(10);
	void *b = malloc(20);
	void *c = malloc(30);
	void *d = malloc(40);

	// printf("a = %p\n", a);
	// printf("b = %p (diff = %ld)\n", b, (long)((char*)b - (char*)a));
	// printf("c = %p (diff = %ld)\n", c, (long)((char*)c - (char*)b));
	// printf("d = %p (diff = %ld)\n", d, (long)((char*)d - (char*)c));

	// printf("a %% 16 = %zu\n", (size_t)a % 16);
	// printf("b %% 16 = %zu\n", (size_t)b % 16);
	// printf("c %% 16 = %zu\n", (size_t)c % 16);
	// printf("d %% 16 = %zu\n", (size_t)d % 16);

	printf("TEST 2:\n");
	double *x = malloc(sizeof(double));
	*x = 3.1415926535;

	// printf("%f\n", *x);

	printf("TEST 3:\n");
	for (int i = 0; i < 2500; i++)
	{
		double *x = malloc(sizeof(double));
		if ((size_t)x % 16 != 0)
		{
			// printf("i = %d -> BAD ALIGN: %p\n", i, x);
			return 1;
		}
		*x = 3.1415926535;
		// free(x);
	}
	
	return 0;
}