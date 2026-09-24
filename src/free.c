#include "../inc/malloc.h"

void free_zone(t_zone* zone, size_t zone_size) {
	if (zone_is_free(zone)) {
		if (zone->prev) {
			if (zone->next)
				zone->prev->next = zone->next;
			else
				zone->prev->next = NULL;
		}
		if (zone->next) {
			if (zone->prev)
				zone->next->prev = zone->prev;
			else
				zone->next->prev = NULL;
		}
		manmap(zone, zone_size);
	}
}


void	free(void *addr) {
	uintptr_t temp_addr;
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;

	temp_addr = (uintptr_t)addr;
	if (addr == NULL)
		return ;
	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				if (cur_block->user_mem_addr == temp_addr) {
					cur_block->is_free = 1;
					//need to be think about


				}
				cur_block = cur_block->next;
				free_zone(cur_zone, TINY_ZONE);
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.small != NULL) {
		cur_zone = g_allocator.small;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				if (cur_block->user_mem_addr == temp_addr) {
					cur_block->is_free = 1;
					// need to be think about

					return ;
				}
				cur_block = cur_block->next;
				free_zone(cur_zone, TINY_ZONE);
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.large != NULL) {
		t_zone* temp_zone;
		cur_zone = g_allocator.large;
		while (cur_zone != NULL) {
			if (temp_addr == cur_zone->blocks->user_mem_addr) {
				temp_zone = cur_zone;
				if (cur_zone->prev != NULL)
					cur_zone->prev->next = cur_zone->next;
				cur_zone = cur_zone->next;
				manmap(temp_zone, round_zone(round_metadata(sizeof(t_zone) + sizeof(t_block)) + temp_zone->blocks->block_size));
			}
		}
	}
}