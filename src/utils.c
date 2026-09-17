#include "../inc/malloc.h"

size_t	round_metadata(size_t metadata_size) {
	if (metadata_size % 16 != 0)
		metadata_size = 16 - metadata_size % 16 + metadata_size;
	return (metadata_size);
}

t_zone	*find_last_zone(t_zone *start) {
	t_zone *last_zone = start;
	while (last_zone->next != NULL)
		last_zone = last_zone->next;
	return (last_zone);
}

