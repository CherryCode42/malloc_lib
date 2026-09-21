#include "../inc/malloc.h"

void show_alloc_mem() {
	while (g_allocator.tiny != NULL) {
		printf("TINY : %p\n", g_allocator.tiny);
		printf("%p - %p", (char *)g_allocator.tiny + g_allocator.tiny->md_size, (char *)g_allocator.tiny->blocks + g_allocator.tiny->blocks->block_size);
		printf(" : %li bytes", g_allocator.tiny->blocks->block_size);
		g_allocator.tiny = g_allocator.tiny->next;
	}
	while (g_allocator.large != NULL) {
		printf("LARGE : %p\n", g_allocator.large);
		printf("%p - %p", (char *)g_allocator.large + g_allocator.large->md_size, (char *)g_allocator.large->blocks + g_allocator.large->blocks->block_size);
		printf(" : %li bytes", g_allocator.large->blocks->block_size);
		g_allocator.large = g_allocator.large->next;
	}
}