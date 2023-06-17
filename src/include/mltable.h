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

#ifdef __cplusplus
extern "C" {
#endif

struct mltable {
	struct table * root;
	size_t	       count;
};

struct mltable init_mltable(void);

struct node * mltable_get(struct table *, KEY_TYPE);

void mltable_set(struct table *, KEY_TYPE, VALUE_TYPE);

#ifdef __cplusplus
}
#endif

#endif /* mltable_h */
