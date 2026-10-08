#include "../inc/malloc.h"

void	extend_allocated_memory(t_block *next, t_block *block, size_t size) {
	if (next->next)
		block->next = next->next;
	else
		block->next = NULL;
	block->block_size += next->block_size + next->tale + sizeof(t_block);
	if (block->block_size - size > sizeof(t_block))
		devide_blocks(block, size);
	return ;
}

void* internal_realloc(void *addr, size_t size) {
	//if there is enough space after allocated block we can prolong the size (if its in same category, TYNY SMALL and LARGE), 
	//if not we need to find new spot for it and copy memory from prev addr to the next addr
	uintptr_t temp_addr;
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;

	temp_addr = (uintptr_t)addr;
	if (addr == NULL)
		return (addr);
	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				if (cur_block->user_mem_addr == temp_addr) {
					t_block* next = cur_block->next;
					if (size <= TINY && (next->is_free && (next->block_size + next->tale + sizeof(t_block) <= size))) {
						//we don't need to move the data, just extend the existing block
							extend_allocated_memory(next, cur_block, size);
						addr = (void*)cur_block->user_mem_addr;
						add_to_history(size, "REALLOC", (void*)temp_addr, addr);
						return (addr);
					}
					else {
						addr = internal_malloc(size);
						memcpy(addr, (void*)cur_block->user_mem_addr, cur_block->block_size);
						add_to_history(size, "REALLOC", (void*)temp_addr, addr);
						internal_free((void*)cur_block->user_mem_addr);
						return (addr);
					}
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
					t_block* next = cur_block->next;
					if (size <= SMALL && (next->is_free && (next->block_size + next->tale + sizeof(t_block) <= size))) {
						//we don't need to move the data, just extend the existing block
							extend_allocated_memory(next, cur_block, size);
						addr = (void*)cur_block->user_mem_addr;
						add_to_history(size, "REALLOC", (void*)temp_addr, addr);
						return (addr);
					}
					else {
						addr = internal_malloc(size);
						memcpy(addr, (void*)cur_block->user_mem_addr, cur_block->block_size);
						add_to_history(size, "REALLOC", (void*)temp_addr, addr);
						internal_free((void*)cur_block->user_mem_addr);
						return (addr);
					}
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.large != NULL) {
		cur_zone = g_allocator.large;
		addr = internal_malloc(size);
		while (cur_zone != NULL) {
			if (temp_addr == cur_zone->blocks->user_mem_addr) {
				memcpy(addr, (void*)cur_zone->blocks->user_mem_addr, cur_zone->blocks->block_size);
				add_to_history(size, "REALLOC", (void*)temp_addr, addr);
				free((void*)cur_zone->blocks->user_mem_addr);
				return (addr);
			}
			cur_zone = cur_zone->next;
		}
	}
	return (addr);
}

void	*realloc(void * addr, size_t size) {
	void *ptr = NULL;

	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	ptr = internal_realloc(addr, size);
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
	return (ptr);
}