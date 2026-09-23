#include "../inc/malloc.h"

size_t	round_metadata(size_t metadata_size) {
	if (metadata_size % 16 != 0)
		metadata_size = 16 - metadata_size % 16 + metadata_size;
	return (metadata_size);
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
	t_block* new_block;
	uintptr_t temp_user_mem_addr;

	new_block = block + size - 1;
	new_block->next = block->next;
	new_block->prev = block;
	temp_user_mem_addr = (uintptr_t)new_block + sizeof(t_block);
	new_block->user_mem_addr = (temp_user_mem_addr + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1); 
	if (new_block->user_mem_addr >= (uintptr_t)(block->next)) // need to check if after alingment we still have place, if not do nothing and return
		return;
	block->next = new_block;
	new_block->block_size = (uintptr_t)new_block->next - new_block->user_mem_addr - 1;
	new_block->is_free = 1;
}