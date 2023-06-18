#include "include/sc_allocator.h"
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>


//static int alloced_count = 0;
static void * __talloc(size_t size) {
//	printf("%i\n", alloced_count ++);
	void * ret = calloc(1, size);
//	void * ret =
//		mmap(NULL, size, PROT_READ | PROT_WRITE,
//		     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	//	memset(ret, 0, size);
	return ret;
}

struct sc_alloc init_allocator(void) {
	struct sc_alloc ret;
	memset(&ret.root, 0, sizeof(ret.root));
	ret.current_chunk = __talloc(sizeof(struct chunk));
	return ret;
}

struct table * allocate(struct sc_alloc * alloc) {
	//	struct table * ret = calloc(1, sizeof(struct table));
	if (alloc->current_chunk_index >= CHUNK_SIZE) {
		alloc->current_chunk_index = 0;
		alloc->current_chunk = __talloc(sizeof(struct chunk));
	}
		
//	struct table * ret = __talloc(sizeof(struct table));
	return &alloc->current_chunk->data[alloc->current_chunk_index ++];
}
