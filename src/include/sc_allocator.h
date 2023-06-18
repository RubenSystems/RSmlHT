//
//  node.h
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#ifndef sc_allocator_h
#define sc_allocator_h

#include "table.h"

#define CHUNK_SIZE 128


#ifdef __cplusplus
extern "C" {
#endif
// ((24 * (2<<4)) * 16) / 4096 CHUNK SIZE for WIDTH 4, SHOULD BE WHOLE NUMBER
// ((128 * (2<<4)) * 16) / 16384 CHUNK SIZE FOR 4 PAGES (allocating 128 pages)

struct chunk {
	struct table data[CHUNK_SIZE];
};

struct sc_alloc {
	struct table   root;
	struct chunk * current_chunk;
	uint16_t       current_chunk_index;
};

struct sc_alloc init_allocator(void);

struct table * allocate(struct sc_alloc *);

#ifdef __cplusplus
}
#endif

	
#endif /* sc_allocator_h */
