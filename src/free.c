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
			else {
				zone->next->prev = NULL;
				if (zone_size == TINY_ZONE)
					g_allocator.tiny = zone->next;
				else
					g_allocator.small = zone->next;
			}
		}
		else {
			if (zone->prev == NULL) {
				if (zone_size == TINY_ZONE)
					g_allocator.tiny = NULL;
				else
					g_allocator.small = NULL;
			}
		}
		munmap(zone, zone_size);
	}
}

void	internal_free(void *addr) {
	uintptr_t temp_addr;
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;
	size_t freed_size;

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
					freed_size = cur_block->user_size;
					if (cur_block->prev && cur_block->prev->is_free) {
						t_block* prev = cur_block->prev;
						if (cur_block->next) {
							prev->next = cur_block->next;
							cur_block->next->prev = prev;
						}
						else
							prev->next = NULL;
						prev->block_size += sizeof(t_block) + cur_block->block_size;
						cur_block = prev;
					}
					if (cur_block->next && cur_block->next->is_free) {
						t_block* next = cur_block->next;
						if (next->next) {
							cur_block->next = next->next;
							next->prev = cur_block;
						}
						else
							cur_block->next = NULL;
						cur_block->block_size += sizeof(t_block) + next->block_size;
					}
					if (BONUS)
						add_to_history(freed_size, "FREE", (void*)cur_block->user_mem_addr, NULL);
					//free_zone(cur_zone, TINY_ZONE);
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
				if (cur_block->user_mem_addr == temp_addr) {
					cur_block->is_free = 1;
					freed_size = cur_block->user_size;
					if (cur_block->prev && cur_block->prev->is_free) {
						t_block* prev = cur_block->prev;
						if (cur_block->next) {
							prev->next = cur_block->next;
							cur_block->next->prev = prev;
						}
						else
							prev->next = NULL;
						prev->block_size += sizeof(t_block) + cur_block->block_size;
						cur_block = prev;
					}
					if (cur_block->next && cur_block->next->is_free) {
						t_block* next = cur_block->next;
						if (next->next){
							cur_block->next = next->next;
							next->prev = cur_block;
						}
						else
							cur_block->next = NULL;
						cur_block->block_size += sizeof(t_block) + next->block_size;
					}
					if (BONUS)
						add_to_history(freed_size, "FREE", (void*)cur_block->user_mem_addr, NULL);
					//free_zone(cur_zone, SMALL_ZONE);
					return ;
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.large != NULL) {
		cur_zone = g_allocator.large;
		while (cur_zone != NULL) {
			if (temp_addr == cur_zone->blocks->user_mem_addr) {
				if (cur_zone->prev) {
					if (cur_zone->next) {
						(cur_zone->prev)->next = cur_zone->next;
						(cur_zone->next)->prev = cur_zone->prev;
					}
					else
						(cur_zone->prev)->next = NULL;
				}
				else {
					if (cur_zone->next) {
						g_allocator.large = cur_zone->next;
						cur_zone->next->prev = NULL;
					}
					else
						g_allocator.large = NULL;
				}
				if (BONUS)
					add_to_history(cur_zone->blocks->user_size, "FREE", (void*)cur_zone->blocks->user_mem_addr, NULL);
				munmap(cur_zone, cur_zone->zone_size);
				return ;
			}
			cur_zone = cur_zone->next;
		}
	}
}

void	free(void *addr) {
	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	ensure_debug_config();
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);

	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	internal_free(addr);
	if (g_debug_cfg.debug && g_debug_cfg.check_level > 0)
		validate_heap();
	if (g_debug_cfg.debug && g_debug_cfg.log_enabled == 1)
		print_free_log(addr);
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
}