#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main(void)
{
	char *ptr_tiny;
	char *ptr_tiny_1;
	char *ptr_small;
	char *ptr_small_1;
	char *ptr_small_2;
	char *ptr_small_3;
	char *ptr_small_4;
	char *ptr_small_5;
	char *ptr_small_6;
	char *ptr_small_7;
	char *ptr_small_8;
	char *ptr_small_9;
	char *ptr_small_10;
	char *ptr_small_11;
	char *ptr_small_12;
	char *ptr_small_13;
	char *ptr_small_14;
	char *ptr_large;
	char *ptr_lagre_1;

	ptr_tiny = malloc(2);
	ptr_tiny_1 = malloc(128);
	ptr_small = malloc(4095);
	ptr_small_1 = malloc(4095);
	ptr_small_2 = malloc(4095);
	ptr_small_3 = malloc(4095);
	ptr_small_4 = malloc(4095);
	ptr_small_5 = malloc(4095);
	ptr_small_6 = malloc(4095);
	ptr_small_7 = malloc(4095);
	ptr_small_8 = malloc(4095);
	ptr_small_9 = malloc(4095);
	ptr_small_10 = malloc(4095);
	ptr_small_11 = malloc(4095);
	ptr_small_12 = malloc(4095);
	ptr_small_13 = malloc(4095);
	ptr_small_14 = malloc(4095);
	ptr_large = malloc(300*1024*1024);
	ptr_lagre_1 = malloc(80847);

	show_alloc_mem();
	printf("Before tiny\n");
	free(ptr_tiny);
	printf("After tiny\n");
	free(ptr_tiny_1);
	//printf("Before small\n");
	free(ptr_small);
	free(ptr_small_1);
	free(ptr_small_2);
	free(ptr_small_3);
	free(ptr_small_4);
	free(ptr_small_5);
	free(ptr_small_6);
	free(ptr_small_7);
	free(ptr_small_8);
	free(ptr_small_9);
	free(ptr_small_10);
	free(ptr_small_11);
	free(ptr_small_12);
	free(ptr_small_13);
	free(ptr_small_14);
	//printf("After small\n");
	//printf("Before large\n");
	free(ptr_large);
	//printf("After large\n");
	free(ptr_lagre_1);

	return (0);
}
