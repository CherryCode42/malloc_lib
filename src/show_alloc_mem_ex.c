#include "../inc/malloc.h"

void	show_alloc_mem_ex() {
	t_history *cur;

	pthread_mutex_lock(&g_allocator.g_malloc_mutex);
	for (size_t i = 0; i < g_allocator.count_records; i++) {
		cur = &g_allocator.history[i];
		putnbr_base(cur->time, 10, 1);
		write(1, " ms", 3);
		if (!strcmp(cur->operation, "MALLOC")) {
			write(1, " MALLOC at 0x", 13);
			putnbr_base((unsigned long)cur->addr, 16, 1);
			write(1, " of ", 4);
			putnbr_base(cur->bytes_nb, 10, 1);
			write(1, " bytes\n", 7);
		}
		else if (!strcmp(cur->operation, "FREE")) {
			write(1, " FREE at 0x", 11);
			putnbr_base((unsigned long)cur->addr, 16, 1);
			write(1, " of ", 4);
			putnbr_base(cur->bytes_nb, 10, 1);
			write(1, " bytes\n", 7);
		}
		else {
			write(1, " REALLOC at 0x", 14);
			putnbr_base((unsigned long)cur->realloc_addr, 16, 1);
			write(1, " from 0x", 8);
			putnbr_base((unsigned long)cur->addr, 16, 1);
			write(1, " of ", 4);
			putnbr_base(cur->bytes_nb, 10, 1);
			write(1, " bytes\n", 7);
		}
	}
	pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
}