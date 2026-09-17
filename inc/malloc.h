#ifndef LIBMALLOC_H
#define LIBMALLOC_H

#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>

#define TINY 128
#define SMALL 4096

#define TINY_ZONE 16384
#define SMALL_ZONE 413696


typedef struct s_block {
	size_t block_size;
	bool is_free;
	struct s_block  *prev;
	struct s_block *next;
} t_block;

typedef struct s_zone {
	int count;
	size_t md_size; //metadata
	size_t zone_size;
	t_block* blocks;
	struct s_zone *next;
} t_zone;

typedef struct s_allocator {
	t_zone *tiny;
	t_zone *small;
	t_zone *large;
} t_allocator;

extern t_allocator g_allocator; //means: There is only one g_allocator in the whole program (it's in malloc.c)


//malloc
// void	*tiny_malloc(size_t size);
// void	*small_malloc(size_t size);
void	*large_malloc(size_t size);

//realloc

//free

//utils
size_t	round_metadata(size_t metadata_size);
t_zone	*find_last_zone(t_zone *start);
void	show_alloc_mem();

#endif