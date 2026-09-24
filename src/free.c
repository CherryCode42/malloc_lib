#include "../inc/malloc.h"

void	free(void *addr) {
	uintptr_t temp;
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;

	temp = (uintptr_t)addr;
	if (addr == NULL)
		return ;
	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				if (temp == cur_block->user_mem_addr) {
					cur_block->is_free = 1;
					if (cur_block->prev->is_free) {
						cur_block->prev->next = cur_block->next;
						cur_block->next->prev = cur_block->prev;
						cur_block->prev->block_size = cur_block->prev->block_size + cur_block->block_size + sizeof(t_block) + cur_block->tale; //count new size of prev block
						cur_block = cur_block->prev; //assign prev block to cur block for easy uniting with next if its free
					}
					if (cur_block->next->is_free) {
						cur_block->next = cur_block->next->next;
						cur_block->prev->block_size = cur_block->block_size + cur_block->next->block_size + sizeof(t_block) + cur_block->next->tale; //count new size of prev block
					}
					return ;
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.small != NULL) {
		cur_zone = g_allocator.small;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				if (temp == cur_block->user_mem_addr) {
					cur_block->is_free = 1;
					if (cur_block->prev->is_free) {
						cur_block->prev->next = cur_block->next;
						cur_block->next->prev = cur_block->prev;
						cur_block->prev->block_size = cur_block->prev->block_size + cur_block->block_size + sizeof(t_block) + cur_block->tale; //count new size of prev block
						cur_block = cur_block->prev; //assign prev block to cur block for easy uniting with next if its free
					}
					if (cur_block->next->is_free) {
						cur_block->next = cur_block->next->next;
						cur_block->prev->block_size = cur_block->block_size + cur_block->next->block_size + sizeof(t_block) + cur_block->next->tale; //count new size of prev block
					}
					return ;
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.large != NULL) {
		t_zone* temp_zone;
		cur_zone = g_allocator.large;
		while (cur_zone != NULL) {
			if (temp == cur_block->user_mem_addr) {
				temp_zone = cur_zone;
				if (cur_zone->prev != NULL)
					cur_zone->prev->next = cur_zone->next;
				cur_zone = cur_zone->next;
				manmap(temp_zone, round_metadata(sizeof(t_zone) + sizeof(t_block)) + temp_zone->blocks->block_size);
			}
		}
	}
}