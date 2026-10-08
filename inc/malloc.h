#ifndef LIBMALLOC_H
#define LIBMALLOC_H

#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <pthread.h>

#define ALIGNMENT 16

#define TINY 128
#define SMALL 4096

#define TINY_ZONE 20480
#define SMALL_ZONE 417792 // for demonstrating can be establish to 40960, to show how it add new zones

#define HISTORY_SIZE 409600

typedef struct s_block {
	size_t block_size;
	size_t tale; //part wich is rest afer aligning user addr (needed when free block and unite with neighbours)
	bool is_free;
	uintptr_t user_mem_addr;
	struct s_block  *prev;
	struct s_block *next;
} t_block;

typedef struct s_zone {
	size_t zone_size;
	t_block* blocks;
	struct s_zone *next;
	struct s_zone *prev;
} t_zone;

typedef struct s_history {
	char* operation;
	void* addr;
	void* realloc_addr;
	int bytes_nb;
	time_t time;
} t_history;

typedef struct s_allocator {
	t_zone *tiny;
	t_zone *small;
	t_zone *large;
	t_history *history;
	size_t count_records; //for history
	time_t start;
	pthread_mutex_t g_malloc_mutex;
} t_allocator;



extern t_allocator g_allocator; //means: There is only one g_allocator in the whole program (it's in malloc.c)

//malloc
void	*malloc(size_t zise);
void	*tiny_malloc(size_t size);
void	*small_malloc(size_t size);
void	*large_malloc(size_t size);
void	*internal_malloc(size_t zise);
t_block	*lockate_new_data(t_block* new_block, t_zone* zone, size_t size, size_t mode, size_t zone_size);

//realloc
void	*realloc(void *addr, size_t size);
void	*internal_realloc(void *addr, size_t size);
void	extend_allocated_memory(t_block *next, t_block *block, size_t size);

//free
void	free(void *addr);
void	internal_free(void *addr);
void	free_zone(t_zone* zone, size_t zone_size);

//utils
uintptr_t	end_of_block(t_block* block);
size_t	round_metadata(size_t metadata_size);
size_t	round_zone(size_t real_size);
t_zone	*find_last_zone(t_zone *start);
void	devide_blocks(t_block* block, size_t size);
int		zone_is_free(t_zone* zone);
void	putnbr_base(unsigned long n, int base);

//utis for bonus
void	add_to_history(size_t bytes_nb, char* operation, void *addr, void *realloc_addr);
time_t	get_time_in_ms(void);
time_t	time_dif(time_t now, time_t past);

//printing memory
void	show_alloc_mem();
void	show_alloc_mem_ex();

#endif