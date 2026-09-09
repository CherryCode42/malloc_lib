#include "../inc/malloc.h"

void	*tiny_malloc(size_t size) {

}

void	*small_malloc(size_t size) {
	
}

void	*large_malloc(size_t size) {
	size_t metadata_size = sizeof(t_zone) + sizeof(t_block);
	if (metadata_size % 16 != 0)
		metadata_size = 16 - metadata_size % 16 + metadata_size;
	size_t real_size = metadata_size + size;
	long page_size = sysconf(_SC_PAGE_SIZE);
	if (real_size % page_size != 0)
		real_size = page_size - real_size % page_size + real_size;
	void *ptr =	mmap(NULL, real_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	char *current = (char *)ptr;
	t_zone* new_zone = (t_zone*)current;
	t_block* new_block = (t_block*)(current + sizeof(t_zone));
	new_zone->blocks = new_block;
	new_zone->zone_size = real_size;
	new_zone->next = NULL;
	new_block->is_free = 0;
	new_block->next = NULL;
	new_block->block_size = size;
	return (current + metadata_size);
}

void	*malloc(size_t size) {
	if (size < TINY)
		return (tiny_mlloc(size));
	else if (size < SMALL)
		return (small_malloc(size));
	else
		return (large_malloc(size));
}