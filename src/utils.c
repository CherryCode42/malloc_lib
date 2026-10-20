#include "../inc/malloc.h"

size_t	round_data(size_t data_size) {
	if (data_size % 16 != 0)
		data_size = 16 - data_size % 16 + data_size;
	return (data_size);
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
void	devide_blocks(t_block* block, size_t size, size_t user_size) { 
	// uintptr_t temp_user_mem_addr;
	uintptr_t user_mem_addr;
	size_t rest_size;

	rest_size = block->block_size - size;
	user_mem_addr = block->user_mem_addr + size + sizeof(t_block);
	block->block_size = size;
	block->user_size = user_size;
	t_block* new_block = (void*)block->user_mem_addr + size;
	t_block* temp;
	temp = block->next;
	block->next = new_block;
	new_block->prev = block;
	if (temp != NULL) {
		new_block->next = temp;
		temp->prev = new_block;
	}
	else
		new_block->next = NULL;
	new_block->user_mem_addr = user_mem_addr;
	new_block->is_free = 1;
	new_block->user_size = 0;
	new_block->block_size = rest_size - sizeof(t_block);
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

//for printing
void putnbr_base(unsigned long n, int base)
{
	char *digits = "0123456789abcdef";

	if (base < 2 || base > 16)
		return;

	if (n >= (unsigned long)base)
		putnbr_base(n / base, base);

	write(1, &digits[n % base], 1);
}

void add_to_history(size_t bytes_nb, char* operation, void *addr, void *realloc_addr) { // for BONUS printing history
	t_history* new_record;

	if (g_allocator.history == NULL) {
		void *ptr =	mmap(NULL, HISTORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); //for BONUS print history
		if (ptr == MAP_FAILED)
			return ;
		g_allocator.history = (t_history*)ptr;
		new_record = g_allocator.history;

	}
	if ((g_allocator.count_records + 1) * sizeof(t_history) > HISTORY_SIZE)
		return;
	new_record = &g_allocator.history[g_allocator.count_records];
	new_record->addr = addr;
	new_record->realloc_addr = realloc_addr;
	new_record->operation = operation;
	new_record->bytes_nb = bytes_nb;
	new_record->time = time_dif(get_time_in_ms(), g_allocator.start);
	g_allocator.count_records++;
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