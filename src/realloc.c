#include "../inc/malloc.h"

void	extend_allocated_memory(t_block *next, t_block *block, size_t size, size_t rounded_size, size_t min_rest) {
	if (next->next) {
		block->next = next->next;
		block->next->prev = block;
	}
	else
		block->next = NULL;
	block->block_size += next->block_size + sizeof(t_block);
	block->user_size = size;
	if (block->block_size - rounded_size > sizeof(t_block) + min_rest)
		devide_blocks(block, rounded_size, size);
	return ;
}

void* relocate_mem(size_t size, void* temp_addr, void* user_mem_addr, size_t old_user_size) {
	void* new_addr = internal_malloc(size);
	size_t size_to_copy;

	if (!new_addr)
		return (NULL);

	if (size >= old_user_size)
		size_to_copy = old_user_size;
	else
		size_to_copy = size;
	memcpy(new_addr, user_mem_addr, size_to_copy);
	internal_free(user_mem_addr);
	add_to_history(size, "REALLOC", (void*)temp_addr, user_mem_addr);
	return (new_addr);
}

void* internal_realloc(void *addr, size_t size) {
	//if there is enough space after allocated block we can prolong the size (if its in same category, TYNY SMALL and LARGE), 
	//if not we need to find new spot for it and copy memory from prev addr to the next addr
	uintptr_t temp_addr;
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;
	size_t rounded_size = round_data(size);
	size_t min_rest;

	temp_addr = (uintptr_t)addr;
	if (addr == NULL)
		return (addr);
	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		min_rest = 16; //min alligned capacity for 1
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				if (cur_block->user_mem_addr == temp_addr) {
					if (cur_block->block_size >= rounded_size) {
						if (cur_block->block_size > rounded_size + sizeof(t_block) + min_rest)
							devide_blocks(cur_block, rounded_size, size);
						else
							cur_block->user_size = size;
						add_to_history(size, "REALLOC", (void*)temp_addr, addr);
						return (addr);
					}
					if (cur_block->next) {
						t_block* next = cur_block->next;
						if (size <= TINY && (next->is_free && (cur_block->block_size + next->block_size + sizeof(t_block) >= rounded_size))) {
						//we don't need to move the data, just extend the existing block
							extend_allocated_memory(next, cur_block, size, rounded_size, min_rest);
							addr = (void*)cur_block->user_mem_addr;
							add_to_history(size, "REALLOC", (void*)temp_addr, addr);
							return (addr);
						}
						else // we move the data
							return (relocate_mem(size, (void*)temp_addr, (void*)cur_block->user_mem_addr, cur_block->user_size));
					}
					else {
						if (cur_block->block_size <= rounded_size) {
							cur_block->user_size = size;
							add_to_history(size, "REALLOC", (void*)temp_addr, addr);
							return (addr);
						}
						else // we move the data
							return (relocate_mem(size, (void*)temp_addr, (void*)cur_block->user_mem_addr, cur_block->user_size));
					}
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.small != NULL) {
		cur_zone = g_allocator.small;
		min_rest = 144;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				if (cur_block->user_mem_addr == temp_addr) {
					if (cur_block->block_size >= rounded_size) {
						if (cur_block->block_size > rounded_size + sizeof(t_block) + min_rest)
							devide_blocks(cur_block, rounded_size, size);
						else
							cur_block->user_size = size;
						add_to_history(size, "REALLOC", (void*)temp_addr, addr);
						return (addr);
					}
					if (cur_block->next) {
						t_block* next = cur_block->next;
						if (size <= SMALL && (next->is_free && (cur_block->block_size + next->block_size + sizeof(t_block) >= rounded_size))) {
							//we don't need to move the data, just extend the existing block
								extend_allocated_memory(next, cur_block, size, rounded_size, min_rest);
							addr = (void*)cur_block->user_mem_addr;
							add_to_history(size, "REALLOC", (void*)temp_addr, addr);
							return (addr);
						}
						else
							return (relocate_mem(size, (void*)temp_addr, (void*)cur_block->user_mem_addr, cur_block->user_size));
					}
					else {
						if (cur_block->block_size <= rounded_size) {
							cur_block->user_size = size;
							add_to_history(size, "REALLOC", (void*)temp_addr, addr);
							return (addr);
						}
						else // we move the data
							return (relocate_mem(size, (void*)temp_addr, (void*)cur_block->user_mem_addr, cur_block->user_size));
					}
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.large != NULL) {
		cur_zone = g_allocator.large;
		while (cur_zone != NULL) {
			if (temp_addr == cur_zone->blocks->user_mem_addr)
				return(relocate_mem(size, (void*)temp_addr, (void*)cur_zone->blocks->user_mem_addr, cur_zone->blocks->user_size));
			cur_zone = cur_zone->next;
		}
		if (cur_zone == NULL)
			addr = NULL;
	}
	return (addr);
}

void	*realloc(void * addr, size_t size) {
	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	ensure_debug_config();
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);

	void *ptr = NULL;

	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	if (addr == NULL) {
		ptr = internal_malloc(size);
		pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
		return (ptr);
	}
	if (size == 0) {
		internal_free(addr);
		ptr = NULL;
		pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
		return (ptr);
	}
	ptr = internal_realloc(addr, size);
	if (g_debug_cfg.debug && g_debug_cfg.check_level > 0)
		validate_heap();
	if (g_debug_cfg.debug && g_debug_cfg.log_enabled == 1)
		print_realloc_log(ptr, size);
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
	return (ptr);
}
