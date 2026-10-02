#include "../inc/malloc.h"

void putnbr_base(unsigned long n, int base)
{
	char *digits = "0123456789abcdef";

	if (base < 2 || base > 16)
		return;

	if (n >= (unsigned long)base)
		putnbr_base(n / base, base);

	write(1, &digits[n % base], 1);
}

void show_alloc_mem() {
	t_zone* cur_zone = NULL;
	t_block* cur_block = NULL;

	if (g_allocator.tiny != NULL) {
		cur_zone = g_allocator.tiny;
		while (cur_zone != NULL) {
			cur_block = cur_zone->blocks;
			write(1, "TINY : ", 7);
			putnbr_base((unsigned long)cur_zone, 16);
			write(1, "\n", 1);
			while (cur_block != NULL) {
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr, 16);
				write(1, " - ", 3);
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr + cur_block->block_size, 16);
				write(1, " : ", 3);
				putnbr_base(cur_block->block_size, 10);
				write (1, " bytes\n", 7);
				if (DEBUG) {
					write(1, "t_block->tale = ", 16);
					putnbr_base(cur_block->tale, 10);
					write(1, "bytes\n", 6);
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
			putnbr_base((unsigned long)cur_zone, 16);
			write(1, "\n", 1);
			cur_block = cur_zone->blocks;
			while (cur_block != NULL) {
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr, 16);
				write(1, " - ", 3);
				write(1, "0x", 2);
				putnbr_base((unsigned long)cur_block->user_mem_addr + cur_block->block_size, 16);
				write(1, " : ", 3);
				putnbr_base(cur_block->block_size, 10);
				write (1, " bytes\n", 7);
				if (DEBUG) {
					write(1, "t_block->tale = ", 16);
					putnbr_base(cur_block->tale, 10);
					write(1, "bytes\n", 6);
				}
				cur_block = cur_block->next;
			}
			cur_zone = cur_zone->next;
		}
	}
	if (g_allocator.large != NULL) {
		cur_zone = g_allocator.large;
		while (cur_zone != NULL) {
			write(1, "LARGE : ", 8);
			putnbr_base((unsigned long)cur_zone, 16);
			write(1, "\n", 1);
			write(1, "0x", 2);
			putnbr_base((unsigned long)cur_zone->blocks->user_mem_addr, 16);
			write(1, " - ", 3);
			write(1, "0x", 2);
			putnbr_base((unsigned long)cur_zone->blocks->user_mem_addr + cur_zone->blocks->block_size, 16);
			write(1, " : ", 3);
			putnbr_base(cur_zone->blocks->block_size, 10);
			write (1, " bytes\n", 7);
			cur_zone = cur_zone->next;
		}
	}
}