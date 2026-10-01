**System calls was used:**  
_void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);_  
- **void \*addr** - is NULL, for the kernel to choose the (page-aligned) address at which to create the mapping
- **size_t length** - amount of bytes needed
- **int prot** - argument describes the desired memory protection of the mapping (PROT_EXEC  Pages may be executed. PROT_READ  Pages may be read. PROT_WRITE Pages may be written. PROT_NONE  Pages may not be accessed.)
- **int flags** - determines whether updates to the mapping are visible to other processes mapping the same region, and whether updates are carried through to the underlying file. (**MAP_SHARED** and **MAP_PRIVATE** describe the disposition of write references to the memory object. If MAP_SHARED is specified, write references shall change the underlying object. If MAP_PRIVATE is specified, modifications to the mapped data by the calling process shall be visible only to the calling process and shall not change the underlying object. It is unspecified whether modifications to the underlying object done after the MAP_PRIVATE mapping is established are visible through the MAP_PRIVATE mapping. Either MAP_SHARED or MAP_PRIVATE can be specified, but not both. The mapping type is retained across fork(). **MAP_ANONYMOUS** The mapping is not backed by any file; its contents are initialized to zero. The fd argument is ignored; however, some  implementations require fd to be -1 if MAP_ANONYMOUS (or MAP_ANON) is specified, and portable applications should  ensure  this. The offset argument should be zero. The use of MAP_ANONYMOUS in conjunction with MAP_SHARED is supported on Linux only since kernel 2.4.)

**How my malloc works:**  
- **“TINY”** mallocs, from 1 to 128 bytes, will be stored in 20480 bytes big zones.  
	_mman needed 5 pages 5*4096=20480  20480 - 17632 = 2848 (extra bytes)_  
- **“SMALL”** mallocs, from 129 to 4096 (page size) bytes, will be stored in 417792 bytes big zones.  
	_mman needed 102 page 102*4096 = 417792 - 413632 = 4160 (extra bytes)_  
- **“LARGE”** mallocs, from 4097 (bigger than page size) bytes, will be allocated outside
the standard memory zones. It is handled by direct using mmap().  