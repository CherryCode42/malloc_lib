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
				printf("%p - %p", (void*)cur_block->user_mem_addr, (void*)cur_block->user_mem_addr + cur_block->block_size);
				printf(" : %li bytes\n", cur_block->block_size);
				if (DEBUG) {
					printf("t_block->tale = %li bytes\n", cur_block->tale);
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.small != NULL) {
		cur_zone = g_allocator.small;
		while (cur_zone != NULL) {
			printf("SMALL : %p\n", cur_zone);
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				printf("%p - %p", (void*)cur_block->user_mem_addr, (void*)cur_block->user_mem_addr + cur_block->block_size - 1);
				printf(" : %li bytes\n", cur_block->block_size);
				if (DEBUG) {
					printf("t_block->tale = %li bytes\n", cur_block->tale);
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	while (g_allocator.large != NULL) {
		printf("LARGE : %p\n", g_allocator.large);
		printf("%p - %p", (void*)g_allocator.large->blocks->user_mem_addr, (void*)g_allocator.large->blocks->user_mem_addr +  g_allocator.large->blocks->block_size);
		printf(" : %li bytes\n", g_allocator.large->blocks->block_size);
		g_allocator.large = g_allocator.large->next;
	}
}