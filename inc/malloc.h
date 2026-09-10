#ifndef LIBMALLOC_H
#define LIBMALLOC_H

#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#define TINY 128
#define SMALL 4096

typedef struct s_allocator {
	t_zone *tiny;
	t_zone *small;
	t_zone *large;
} t_allocator;

extern t_allocator g_allocator;

typedef struct s_block {
	size_t block_size;
	bool is_free;
	struct t_block *next;
} t_block;

typedef struct s_zone {
	int count;
	size_t zone_size;
	t_block* blocks;
	struct t_zone *next;
} t_zone;

//malloc
void	*tiny_malloc(size_t size);
void	*small_malloc(size_t size);
void	*large_malloc(size_t size);

//realloc

//free

//utils
size_t round_metadata(size_t metadata_size);

#endif