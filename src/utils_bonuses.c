#include "../inc/malloc.h"


void add_to_history(size_t bytes_nb, char* operation, void *addr, void *realloc_addr) { // for BONUS printing history
	t_history* new_record;

	if (BONUS) {
		if (g_allocator.history == NULL) {
			void *ptr =	mmap(NULL, HISTORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); //for BONUS print history
			if (ptr == MAP_FAILED)
				return ;
			g_allocator.history = (t_history*)ptr;
			new_record = g_allocator.history;

		}
		if ((g_allocator.count_records + 1) * sizeof(t_history) > HISTORY_SIZE)
			return ;
		new_record = &g_allocator.history[g_allocator.count_records];
		new_record->addr = addr;
		new_record->realloc_addr = realloc_addr;
		new_record->operation = operation;
		new_record->bytes_nb = bytes_nb;
		new_record->time = time_dif(get_time_in_ms(), g_allocator.start);
		g_allocator.count_records++;
	}
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	time_dif(time_t now, time_t past)
{
	time_t	res;

	res = now - past;
	return (res);
}

int validate_heap() {
	t_zone* cur_zone;
	t_block* cur_block;

	cur_zone = g_allocator.tiny;
	while (cur_zone != NULL) {
		cur_block = cur_zone->blocks;
		while (cur_block != NULL) {
			if (!cur_block->is_free && cur_block->user_mem_addr == 0) {
				return (0); // Invalid heap: allocated block with null user memory address
			}
			if (cur_block->block_size == 0)
				return (0); // Invalid heap: allocated block with 0 size
			if (cur_block->user_mem_addr < (uintptr_t)cur_zone ||
				cur_block->user_mem_addr >= (uintptr_t)cur_zone + TINY_ZONE)
				return (0); // Invalid heap: user addres isn't inside block allockation zone
			//check_connections
			if (cur_block->next && cur_block->next->prev != cur_block)
				return (0); // Invalid heap: connection between blockes is corrupted
			if (cur_block->prev && cur_block->prev->next != cur_block)
				return (0); // Invalid heap: connection between blockes is corrupted
			cur_block = cur_block->next;
		}
		cur_zone = cur_zone->next;
	}
	cur_zone = g_allocator.small;
	while (cur_zone != NULL) {
		cur_block = cur_zone->blocks;
		while (cur_block != NULL) {
			if (!cur_block->is_free && cur_block->user_mem_addr == 0)
				return (0);
			if (cur_block->block_size == 0)
				return (0);
			if (cur_block->user_mem_addr < (uintptr_t)cur_zone ||
				cur_block->user_mem_addr >= (uintptr_t)cur_zone + SMALL_ZONE)
				return (0);
			if (cur_block->next && cur_block->next->prev != cur_block)
				return (0);
			if (cur_block->prev && cur_block->prev->next != cur_block)
				return (0);
			cur_block = cur_block->next;
			}
		cur_zone = cur_zone->next;
	}

	cur_zone = g_allocator.large;
	while (cur_zone != NULL) {
		cur_block = cur_zone->blocks;
		while (cur_block != NULL) {
			if (!cur_block->is_free && cur_block->user_mem_addr == 0)
				return (0);
			if (cur_block->block_size == 0)
				return (0);
			if (cur_block->user_mem_addr < (uintptr_t)cur_zone ||
				cur_block->user_mem_addr >= (uintptr_t)cur_zone + cur_zone->zone_size)
				return (0);
			cur_block = cur_block->next;
		}
		cur_zone = cur_zone->next;
	}

	//validate connections between blocks
	write (1, "[DEBUG] Allocator works well\n", 29);
	return (1); // Heap is valid
}

void print_malloc_log(void* ptr, size_t size) {
	int fd = open("malloc_debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);

	if (fd >= 0)
	{
		write(fd, "[DEBUG] MALLOC at 0x", 20);
		putnbr_base((unsigned long)ptr, 16, fd);
		write(fd, " of ", 4);
		putnbr_base(size, 10, fd);
		write(fd, " bytes\n", 7);
		close(fd);
	}

}

void print_free_log(void* ptr) {
	int fd = open("malloc_debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);

	if (fd >= 0) {
		write(fd, "[DEBUG] FREE at 0x", 18);
		putnbr_base((unsigned long)ptr, 16, fd);
		write(fd, "\n", 1);
	}
}

void print_realloc_log(void* ptr, size_t size) {
	int fd = open("malloc_debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);

	if (fd >= 0) {
		write(fd, "[DEBUG] REALLOC at 0x", 18);
		putnbr_base((unsigned long)ptr, 16, fd);
		write(fd, " of ", 4);
		putnbr_base(size, 10, fd);
		write(fd, " bytes\n", 7);
	}
}