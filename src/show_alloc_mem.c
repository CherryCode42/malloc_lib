#include "../inc/malloc.h"

void show_alloc_mem() {
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;

	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			write(1, "TINY : ", 7);
			putnbr_base((unsigned long)cur_zone, 16);
			write(1, "\n", 1);
			while (cur_block != NULL) {
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr, 16);
				write(1, " - ", 3);
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr + cur_block->block_size, 16);
				write(1, " : ", 3);
				putnbr_base(cur_block->block_size, 10);
				write (1, " bytes\n", 7);
				if (DEBUG) {
					write(1, "t_block->tale = ", 16);
					putnbr_base(cur_block->tale, 10);
					write(1, "bytes\n", 6);
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
			putnbr_base((unsigned long)cur_zone, 16);
			write(1, "\n", 1);
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr, 16);
				write(1, " - ", 3);
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr + cur_block->block_size, 16);
				write(1, " : ", 3);
				putnbr_base(cur_block->block_size, 10);
				write (1, " bytes\n", 7);
				if (DEBUG) {
					write(1, "t_block->tale = ", 16);
					putnbr_base(cur_block->tale, 10);
					write(1, "bytes\n", 6);
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
			putnbr_base((unsigned long)cur_zone, 16);
			write(1, "\n", 1);
			write(1, "0x", 2);
			putnbr_base((unsigned long)cur_zone->blocks->user_mem_addr, 16);
			write(1, " - ", 3);
			write(1, "0x", 2);
			putnbr_base((unsigned long)cur_zone->blocks->user_mem_addr + cur_zone->blocks->block_size, 16);
			write(1, " : ", 3);
			putnbr_base(cur_zone->blocks->block_size, 10);
			write (1, " bytes\n", 7);
			cur_zone = cur_zone->next;
		}
	}
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
}