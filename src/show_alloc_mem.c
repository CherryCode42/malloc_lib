#include "../inc/malloc.h"

void show_alloc_mem() {
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;

	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			write(1, "TINY : ", 7);
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
			write(1, "SMALL : ", 8);
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
	if (g_allocator.large != NULL) {
		cur_zone = g_allocator.large;
		while (cur_zone != NULL) {
			write(1, "LARGE : ", 8);
			printf("%p - %p", (void*)cur_zone->blocks->user_mem_addr, (void*)cur_zone->blocks->user_mem_addr + cur_zone->blocks->block_size);
			printf(" : %li bytes\n", cur_zone->blocks->block_size);
			cur_zone = cur_zone->next;
		}
	}
}