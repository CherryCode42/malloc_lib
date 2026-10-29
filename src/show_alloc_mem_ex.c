#include "../inc/malloc.h"

void	print_hex(unsigned char c)
{
	char	*hex;

	hex = "0123456789abcdef";
	write(1, &hex[c / 16], 1);
	write(1, &hex[c % 16], 1);
}

void	print_hex_dump(void *ptr, size_t size)
{
	unsigned char	*bytes;
	size_t		i;

	bytes = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		print_hex(bytes[i]);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	show_hex_dump() {
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;
	unsigned char	*hex;

	if (BONUS) {
		pthread_mutex_lock(&g_allocator.g_malloc_mutex);
		if (g_allocator.tiny != NULL) {
			cur_zone = g_allocator.tiny;
			while (cur_zone != NULL ) {
				cur_block = cur_zone->blocks;
				write(1, "TINY : ", 7);
				putnbr_base((unsigned long)cur_zone, 16, 1);
				write(1, "\n", 1);
				while (cur_block != NULL) {
					hex = (unsigned char *)cur_block->user_mem_addr;
					if (!cur_block->is_free) {
						write(1, "0x", 2);
						putnbr_base((unsigned long)cur_block->user_mem_addr, 16, 1);
						write(1, ": ", 2);
						print_hex_dump(hex, cur_block->user_size);
					}
					cur_block = cur_block->next;
				}
				cur_zone = cur_zone->next;
			}
		}
		if (g_allocator.small != NULL) {
			cur_zone = g_allocator.small;
			while (cur_zone != NULL) {
				write(1, "SMALL : ", 8);
				putnbr_base((unsigned long)cur_zone, 16, 1);
				write(1, "\n", 1);
				cur_block = cur_zone->blocks;
				while (cur_block != NULL) {
					hex = (unsigned char *)cur_block->user_mem_addr;
					if (!cur_block->is_free) {
						write(1, "0x", 2);
						putnbr_base((unsigned long)cur_block->user_mem_addr, 16, 1);
						write(1, ": ", 2);
						print_hex_dump(hex, cur_block->user_size);
						write(1, "\n", 1);
					}
					cur_block = cur_block->next;
				}
				cur_zone = cur_zone->next;
			}
		}
		if (g_allocator.large != NULL) {
			cur_zone = g_allocator.large;
			while (cur_zone != NULL) {
				hex = (unsigned char *)cur_zone->blocks->user_mem_addr;
				write(1, "LARGE : ", 8);
				putnbr_base((unsigned long)cur_zone, 16, 1);
				write(1, "\n", 1);
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_zone->blocks->user_mem_addr, 16, 1);
				write(1, ": ", 2);
				print_hex_dump(hex, cur_zone->blocks->user_size);
				write(1, "\n", 1);
				cur_zone = cur_zone->next;
			}
		}
		pthread_mutex_unlock(&g_allocator.g_malloc_mutex);
	}
}

void	show_history(t_allocator g_allocator) {
	t_history *cur;

	if (BONUS) {
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
}

void	show_alloc_mem_ex(const char *mode) {
	if (mode != NULL && !strcmp(mode, "HISTORY"))
		show_history(g_allocator);
	else if (mode != NULL && !strcmp(mode, "DUMP"))
		show_hex_dump();
	}