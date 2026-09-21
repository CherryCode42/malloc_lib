#include "../inc/malloc.h"

void show_alloc_mem() {
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;

	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		cur_block = cur_zone->blocks;
		while (cur_zone != NULL) {
			printf("TINY : %p\n", cur_zone);
			while (cur_block != NULL) {
				printf("%p - %p", cur_block->user_mem_addr, cur_block->user_mem_addr + cur_block->block_size);
				printf(" : %li bytes\n", g_allocator.tiny->blocks->block_size);
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	while (g_allocator.large != NULL) {
		printf("LARGE : %p\n", g_allocator.large);
		printf("%p - %p", g_allocator.large->blocks->user_mem_addr,  g_allocator.large->blocks->user_mem_addr +  g_allocator.large->blocks->block_size);
		printf(" : %li bytes", g_allocator.large->blocks->block_size);
		g_allocator.large = g_allocator.large->next;
	}
}