#include "../inc/malloc.h"

size_t	round_metadata(size_t metadata_size) {
	if (metadata_size % 16 != 0)
		metadata_size = 16 - metadata_size % 16 + metadata_size;
	return (metadata_size);
}

size_t round_zone(size_t real_size) {
	long page_size = sysconf(_SC_PAGE_SIZE);
	if (real_size % page_size != 0)
		real_size = page_size - real_size % page_size + real_size;
	return (real_size);
}

t_zone	*find_last_zone(t_zone *start) {
	t_zone *last_zone = start;
	while (last_zone->next != NULL)
		last_zone = last_zone->next;
	return (last_zone);
}

uintptr_t end_of_block(t_block* block) {
	uintptr_t block_end;
	
	block_end = (uintptr_t)block + sizeof(t_block) + block->block_size - 1;
	return (block_end);
}

//ToDO: this function needs to be tested after writing free function!!!!!!!!!!!!!!!!!!!
void	devide_blocks(t_block* block, size_t size) { 
	uintptr_t temp_user_mem_addr;
	uintptr_t user_mem_addr;
	size_t rest_size;


	rest_size = block->block_size - size;
	if (rest_size > sizeof(t_block)) {
		temp_user_mem_addr = block->user_mem_addr + size + sizeof(t_block);
		user_mem_addr = (temp_user_mem_addr + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
		if (user_mem_addr >= (uintptr_t)(block->next)) // need to check if after alingment we still have place, if not do nothing and return
			return;
		block->block_size = size;
		t_block* new_block = (void*)block->user_mem_addr + size;
		t_block* temp;
		temp = block->next;
		block->next = new_block;
		new_block->prev = block;
		if (temp)
			new_block->next = temp;
		else
			new_block->next = NULL;
		new_block->user_mem_addr = user_mem_addr;
		new_block->is_free = 1;
		new_block->tale = new_block->user_mem_addr - (uintptr_t)new_block - sizeof(t_block);
		new_block->block_size = rest_size - sizeof(t_block) - new_block->tale;
	}
}

int	zone_is_free(t_zone* zone) {
	t_block* cur_block;

	cur_block = zone->blocks;
	while (cur_block != NULL) {
		if (!cur_block->is_free)
			return (0);
		cur_block = cur_block->next;
	}
	return (1);
}