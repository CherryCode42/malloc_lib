#include "../inc/malloc.h"

void* realloc(void *addr, size_t size) {
	//if there is enough space after allocated block we can prolong the size (if its in same category, TYNY SMALL and LARGE), 
	//if not we need to find new spot for it and copy memory from prev addr to the next addr
}