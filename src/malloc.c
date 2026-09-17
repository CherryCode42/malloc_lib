#include "../inc/malloc.h"

t_allocator g_allocator = {
	.tiny = NULL,
	.small = NULL,
	.large = NULL
};

static size_t round_zone(size_t real_size) {
	long page_size = sysconf(_SC_PAGE_SIZE);
	if (real_size % page_size != 0)
		real_size = page_size - real_size % page_size + real_size;
	return (real_size);
}

static void* allocate_new_zone(size_t size_of_zone) {
	void *ptr =	mmap(NULL, size_of_zone, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
}

t_block* lockate_new_data(t_zone* zone, size_t size, size_t mode) {
	t_block* new_block;
	t_block* current = zone->blocks;
	size_t min_suitable = mode;

	new_block->block_size = size;
	while (zone->next != NULL) {
		while (current->next != NULL) {
			if (current->block_size > size && current->is_free) {
				if (min_suitable > current->block_size - size)
					new_block = current;
			}
			else
				current = current->next;
		}
	}
	if (current->block_size < size)
		return (NULL);
	else {
		if (min_suitable > current->block_size - size)
					new_block = current;
	}
		
}

void	*tiny_malloc(size_t size) {
	t_block* new_block;
	new_block = lockate_new_data(g_allocator.tiny, size, TINY);
	if (g_allocator.tiny == NULL || !new_block) {
		void *ptr = allocate_new_zone(TINY_ZONE);
		if (!ptr)
			return (NULL);
		char *current = (char *)ptr;
		t_zone* new_zone = (t_zone*)current;
		new_block = (t_block*)(current + sizeof(t_zone));
		new_zone->count = 1;
		new_zone->next = NULL;
		new_zone->blocks = new_block;
		new_block->block_size = size;
		new_block->next = new_block + size;
		new_block->next->is_free = 1;
		new_block->next->block_size = TINY_ZONE - sizeof(t_zone) - sizeof(t_block)*2;
		new_block->prev = NULL;
		new_block->is_free = 0;
	}
	

}

// void	*small_malloc(size_t size) {
	
// }

void	*large_malloc(size_t size) {
	size_t metadata_size = sizeof(t_zone) + sizeof(t_block);
	metadata_size = round_metadata(metadata_size); //do metadata size divisible by 16 for the efficiency
	size_t real_size = metadata_size + size;
	real_size = round_zone(real_size);
	void *ptr =	mmap(NULL, real_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	char *current = (char *)ptr;
	t_zone* new_zone = (t_zone*)current;
	t_block* new_block = (t_block*)(current + sizeof(t_zone));
	new_zone->blocks = new_block;
	new_zone->zone_size = real_size;
	new_zone->md_size = metadata_size;
	new_zone->next = NULL;
	new_block->is_free = 0;
	new_block->next = NULL;
	new_block->block_size = size;
	if (g_allocator.large != NULL) {
		t_zone * last_large_zone = find_last_zone(g_allocator.large);
		last_large_zone->next = new_zone;
	}
	else
		g_allocator.large = new_zone;
	return (current + metadata_size);
}

void	*malloc(size_t size) {
	// if (size < TINY)
	// 	return (tiny_malloc(size));
	// else if (size < SMALL)
	// 	return (small_malloc(size));
	// else
	long int block_size =  sizeof(t_block);
	long int zone_size =  sizeof(t_zone);
	printf("sizeof t_block %zu = ", block_size);
	printf("\nsizeof t_zone %zu = ", zone_size);
	return (large_malloc(size));
}