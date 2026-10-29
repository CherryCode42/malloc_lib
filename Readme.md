# ***Malloc. Post Core project from UNIX chapter of RNCP7 from 42.***
_Project is done by post core student of 42Prague iarefeva_

This project was done in order to deepen an understanding of Unix memory organization, dynamic allocation mechanisms, and low-level system interactions. It explores how memory is managed at runtime, how the kernel handles virtual memory, and how custom allocators can be built using system calls such as mmap and munmap.

**System calls was used:**  
_void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);_  
System call creates a new mapping in the virtual address space of the calling process.
- **void \*addr** - is NULL, for the kernel to choose the (page-aligned) address at which to create the mapping
- **size_t length** - amount of bytes needed
- **int prot** - argument describes the desired memory protection of the mapping (PROT_EXEC  Pages may be executed. PROT_READ  Pages may be read. PROT_WRITE Pages may be written. PROT_NONE  Pages may not be accessed.)
- **int flags** - determines whether updates to the mapping are visible to other processes mapping the same region, and whether updates are carried through to the underlying file. (**MAP_SHARED** and **MAP_PRIVATE** describe the disposition of write references to the memory object. If MAP_SHARED is specified, write references shall change the underlying object. If MAP_PRIVATE is specified, modifications to the mapped data by the calling process shall be visible only to the calling process and shall not change the underlying object. It is unspecified whether modifications to the underlying object done after the MAP_PRIVATE mapping is established are visible through the MAP_PRIVATE mapping. Either MAP_SHARED or MAP_PRIVATE can be specified, but not both. The mapping type is retained across fork(). **MAP_ANONYMOUS** The mapping is not backed by any file; its contents are initialized to zero. The fd argument is ignored; however, some  implementations require fd to be -1 if MAP_ANONYMOUS (or MAP_ANON) is specified, and portable applications should  ensure  this. The offset argument should be zero. The use of MAP_ANONYMOUS in conjunction with MAP_SHARED is supported on Linux only since kernel 2.4.)  

_int munmap(void *addr, size_t length)_  
System call deletes the mappings for the specified address range, and causes further references to addresses within the range to generate invalid memory references.

## **How my custom malloc works:**

This allocator follows a segregated allocation strategy and is organized into three main memory classes: TINY, SMALL, and LARGE.  

- TINY and SMALL allocations are managed inside preallocated memory zones created with mmap. Each zone contains a linked list of metadata blocks, and each block stores its size, allocation state, and pointer to the user memory area. The allocator first searches existing free blocks to reuse space efficiently, and if no suitable block is found, it creates a new zone.
- LARGE allocations are handled separately: each allocation is mapped as its own dedicated memory region, which allows bigger requests to bypass the fixed-size zone strategy and avoids wasting space in the small-block pools.
- The project also keeps track of zone lists for each category, which makes freeing, reallocating, and memory inspection easier and more predictable.
- In other words, the allocator combines mmap-based zone allocation, block metadata tracking, and linked-list traversal to provide a custom memory manager similar in spirit to standard allocators, while keeping the logic simple and transparent.

**“TINY”** mallocs, from 1 to 128 bytes, will be stored in 20480 bytes big zones.  
	_mman needed 5 pages 5*4096=20480  20480 - 17632 = 2848 (extra bytes)_

**“SMALL”** mallocs, from 129 to 4096 (page size) bytes, will be stored in 417792 bytes big zones.  
	_mman needed 102 page 102*4096 = 417792 - 413632 = 4160 (extra bytes)_

**“LARGE”** mallocs, from 4097 (bigger than page size) bytes, will be allocated outside
the standard memory zones. It is handled by direct using mmap().  

## **Additional features:**

- `show_alloc_mem()` prints the currently allocated memory ranges grouped by size class.
- `show_alloc_mem_ex(char *mode)` prints the allocator event history with timestamps, operation type, and addresses for debugging and hexadecimal dump of allocated memory. For the history you need to pass "History" as mode, and for the hexadecimal dump "DUMP".
- Debug mode is supported through environment variables such as `MALLOC_DEBUG`, `MALLOC_CHECK`, and `MALLOC_LOG`, enabling runtime validation and logging.
- `validate_heap()` checks the allocator structure and helps detect corrupted metadata or invalid block states.
- The allocator maintains operation history for debugging, making it easier to trace malloc, free, and realloc calls during testing.
- Thread-safety is ensured with a global pthread mutex, so allocator operations such as malloc, free, realloc, and memory inspection are protected against concurrent access from multiple threads.

## **Useful notes for proper work with library**
To compile program with custom malloc library use
```
gcc -DBONUS=0 -DDEBUG=0 <program>.c -I./inc -L. -lft_malloc -o <program>
```

To start program with custom malloc library use
```
LD_LIBRARY_PATH=. ./<program>
```

To use debug features env variables should be exported
```
export MALLOC_DEBUG=1
export MALLOC_CHECK=1
export MALLOC_LOG=1
```
and -DDEBUG flad should be established equal 1 while compile the library

## **Used resourses:**

- Articles and explanations about the original malloc implementation and memory allocation strategies.
- Unix manual pages (`man mmap`, `man malloc`, `man munmap`) and documentation on virtual memory management.
- Linux documentation on memory mapping, page-aligned allocations, and process memory layout.