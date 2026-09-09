#ifndef LIBMALLOC_H
#define LIBMALLOC_H

#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#define TINY 128
#define SMALL 4026

typedef struct s_zone {
	size_t zone_size;
	t_block* blocks;
	struct t_zone *next;
} t_zone;

typedef struct s_block {
	size_t block_size;
	bool is_free;
	struct t_block *next;
} t_block;

#endif