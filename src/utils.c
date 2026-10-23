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
	uintptr_t user_mem_addr;
	size_t rest_size;

	if (block == NULL || size == 0 || size > block->block_size)
		return ;
	rest_size = block->block_size - size;
	if (rest_size < sizeof(t_block) + ALIGNMENT)
		return ;
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
void putnbr_base(unsigned long n, int base, int fd)
{
	char *digits = "0123456789abcdef";

	if (base < 2 || base > 16)
		return;

	if (n >= (unsigned long)base)
		putnbr_base(n / base, base, fd);

	write(fd, &digits[n % base], 1);
}
