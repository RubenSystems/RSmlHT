//
//  mltable.h
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#ifndef mltable_h
#define mltable_h

#include <stdio.h>

#include "config.h"
#include "table.h"
#include "node.h"
#include "sc_allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mltable {
	struct table *	root;
	size_t		count;
	struct sc_alloc * allocator;
};

struct mltable init_mltable(struct sc_alloc *);

struct node * mltable_get(struct table *, KEY_TYPE);

void mltable_set(struct mltable *, KEY_TYPE, VALUE_TYPE);

#ifdef __cplusplus
}
#endif

#endif /* mltable_h */
