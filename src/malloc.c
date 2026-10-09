#include "../inc/malloc.h"

t_allocator g_allocator = {
	.tiny = NULL,
	.small = NULL,
	.large = NULL,
	.history = NULL,
	.count_records = 0,
	.start = 0,
	.g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER,
};

t_block* lockate_new_data(t_block* new_block, t_zone* zone, size_t size, size_t mode, size_t zone_size) {
	t_zone* cur_zone = zone;

	if (zone == NULL)
		return (NULL);

	t_block* cur_block = zone->blocks;
	size_t diff = mode; //difference between needed size and free amount of bytes in block
	size_t cur_diff; //we need two of them to remember the lowest
	uintptr_t zone_end; //last byte of zone

	while (cur_zone!= NULL) {
		zone_end = (uintptr_t)cur_zone + zone_size - 1;
		cur_block = cur_zone->blocks;
		while (cur_block != NULL) {
			if (cur_block->block_size >= size && cur_block->is_free) {
				cur_diff = cur_block->block_size - size;
				if (cur_diff < diff) { //check the difference if its lower we need to allockate in this block
					diff = cur_diff; 
					new_block = cur_block;
					cur_block->is_free = 0;
					if (new_block->block_size - size > sizeof(t_block))
						devide_blocks(new_block, size);
				}
				return (new_block);
			}
			if (cur_block->next == NULL) {
				size_t rest_amount_mem = zone_end - end_of_block(cur_block);
				if (rest_amount_mem > size + sizeof(t_block)) {	//if there is space after all occupied blocks in zone
					new_block = (t_block*)((char*)cur_block
							+ sizeof(t_block) + cur_block->block_size
							+ cur_block->tale);	//we can allocate new block there
					uintptr_t temp_user_mem_addr = (uintptr_t)new_block + sizeof(t_block);
					new_block->user_mem_addr = (temp_user_mem_addr + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
					if (zone_end - new_block->user_mem_addr < size) //we need to check if it's enough memory for user with addr alingment
						return (NULL);
					cur_block->next = new_block;
					new_block->next = NULL;
					new_block->tale = new_block->user_mem_addr - (uintptr_t)new_block - sizeof(t_block); //needed for control during developing, can be deleted
					new_block->prev = cur_block;
					new_block->block_size = size;
					new_block->is_free = 0;
					return (new_block);
				}
			}
			cur_block = cur_block->next;
		}
		cur_zone = cur_zone->next;
	}
	return (new_block);
}

void* tiny_malloc(size_t size) {
	void* addr;
	t_block* new_block = NULL;
	new_block = lockate_new_data(new_block, g_allocator.tiny, size, TINY, TINY_ZONE);
	if (!new_block) { //if we couldn't find any place for the new block in existed zones wee need a new one
			void *ptr =	mmap(NULL, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
			if (ptr == MAP_FAILED)
				return (NULL);
			char *current = (char *)ptr;
			t_zone* new_zone = (t_zone*)current;
			if (g_allocator.tiny == NULL)
				g_allocator.tiny = new_zone;
			else {
				t_zone* temp = g_allocator.tiny;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = new_zone;
			}
			new_block = (t_block*)(current + sizeof(t_zone));
			uintptr_t temp_user_mem_addr = (uintptr_t)new_block + sizeof(t_block);
			new_block->user_mem_addr = (temp_user_mem_addr + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
			new_block->tale = new_block->user_mem_addr - (uintptr_t)new_block - sizeof(t_block); //needed for control during developing, can be deleted
			new_zone->next = NULL;
			new_zone->blocks = new_block;
			new_block->block_size = size;
			new_block->next = NULL;
			new_block->prev = NULL;
			new_block->is_free = 0;
	}
	addr = (void*)new_block->user_mem_addr;
	add_to_history(size, "MALLOC", addr, NULL);
	return (addr);
}

void	*small_malloc(size_t size) {
	void* addr;
	t_block* new_block = NULL;
	new_block = lockate_new_data(new_block, g_allocator.small, size, SMALL, SMALL_ZONE);
	if (!new_block) { //if we couldn't find any place for the new block in existed zones wee need a new one
		void *ptr =	mmap(NULL, SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
			if (ptr == MAP_FAILED)
				return (NULL);
			char *current = (char *)ptr;
			t_zone* new_zone = (t_zone*)current;
			if (g_allocator.small == NULL)
				g_allocator.small = new_zone;
			else {
				t_zone* temp = g_allocator.small;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = new_zone;
			}
			new_block = (t_block*)(current + sizeof(t_zone));
			uintptr_t temp_user_mem_addr = (uintptr_t)new_block + sizeof(t_block);
			new_block->user_mem_addr = (temp_user_mem_addr + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
			new_block->tale = new_block->user_mem_addr - (uintptr_t)new_block - sizeof(t_block); //needed for control during developing, can be deleted
			new_zone->next = NULL;
			new_zone->blocks = new_block;
			new_block->block_size = size;
			new_block->next = NULL;
			new_block->prev = NULL;
			new_block->is_free = 0;
	}
	addr = (void*)new_block->user_mem_addr;
	add_to_history(size, "MALLOC", addr, NULL);
	return (addr);
}

void	*large_malloc(size_t size) {
	void* addr;
	size_t metadata_size = sizeof(t_zone) + sizeof(t_block);
	metadata_size = round_metadata(metadata_size); //do metadata size divisible by 16 for the efficiency
	size_t real_size = metadata_size + size;
	real_size = round_zone(real_size);
	void *ptr =	mmap(NULL, real_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	uintptr_t current = (uintptr_t)ptr;
	t_zone* new_zone = (t_zone*)current;
	t_block* new_block = (t_block*)(current + sizeof(t_zone));
	new_zone->blocks = new_block;
	new_zone->zone_size = real_size;
	new_zone->next = NULL;
	new_zone->prev = NULL;
	new_block->is_free = 0;
	new_block->next = NULL;
	new_block->prev = NULL;
	new_block->block_size = size;
	new_block->user_mem_addr = current + metadata_size;
	if (g_allocator.large != NULL) {
		t_zone * last_large_zone = find_last_zone(g_allocator.large);
		last_large_zone->next = new_zone;
		new_zone->prev = last_large_zone;
	}
	else
		g_allocator.large = new_zone;
	addr = (void*)new_block->user_mem_addr;
	add_to_history(size, "MALLOC", addr, NULL);
	return (addr);
}

void	*internal_malloc(size_t size) {
	if (size <= TINY)
		return tiny_malloc(size);
	else if (size <= SMALL)
		return small_malloc(size);
	else
		return large_malloc(size);
}

void	*malloc(size_t size) {
	void *ptr = NULL;

	g_allocator.start = get_time_in_ms();
	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	ptr = internal_malloc(size);
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
	return (ptr);
}
