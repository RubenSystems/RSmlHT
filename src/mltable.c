//
//  mltable.c
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#include "include/mltable.h"
#include "include/table.h"

#include <stdbool.h>
#include <stdlib.h>

#define INITIAL_TABLE_WIDTH	6
#define DEEP_TABLE_WIDTH	5
#define THRESHOLD_TABLE_WIDTH	3
#define TABLE_SIZE(WIDTH)	(2 << WIDTH)
#define TABLE_WIDTH(LAYER)	INITIAL_TABLE_WIDTH
#define TABLE_WIDTH_MASK(LAYER) (1 << (TABLE_WIDTH(LAYER) + 1)) - 1

struct mltable init_mltable(void) {
	struct mltable ret = { init_table(TABLE_SIZE(INITIAL_TABLE_WIDTH)), 0 };
	return ret;
}

static size_t __layer_key(KEY_TYPE key, uint32_t layer) {
	return TABLE_WIDTH_MASK(layer) & (key >> (layer * TABLE_WIDTH(layer)));
}

struct node * mltable_get(void * table, KEY_TYPE key) {
	struct node * ret;
	int	      layer = 0;

	while (1) {
		ret = get_table_node(table, __layer_key(key, layer++));
		if (ret->type == NODE_POINTER) {
			table = ret->data.pointer;
		} else {
			break;
		}
	};

	return ret;
}

static bool equatable(KEY_TYPE a, KEY_TYPE b) {
	return a == b;
}
static void
__set_helper(void * table, KEY_TYPE key, VALUE_TYPE value, uint32_t layer) {
	struct node * ret;
	bool	      selection = true;
	while (selection) {
		ret = get_table_node(table, __layer_key(key, layer));

		switch (ret->type) {
		case NODE_NOTHING: {
			ret->data.value = value;
			ret->key	= key;
			ret->type	= NODE_DATA;
			selection	= false;
		} break;
		case NODE_DATA: {
			if (equatable(key, ret->key)) {
				ret->data.value = value;
			} else {
				void * new_table = init_table(
					TABLE_SIZE(TABLE_WIDTH(layer + 1))
				);

				__set_helper(
					new_table, ret->key, ret->data.value,
					layer + 1
				);
				__set_helper(new_table, key, value, layer + 1);
				ret->key	  = 0;
				ret->data.pointer = new_table;
				ret->type	  = NODE_POINTER;
			}
			selection = false;
		} break;
		case NODE_POINTER: {
			table = ret->data.pointer;
			layer++;
			selection = false;
		} break;
		default: {
			printf("SOMETHING IS BROKEN!\n");
			exit(200);
		}
		}
	}
}

void mltable_set(void * table, KEY_TYPE key, VALUE_TYPE value) {
	__set_helper(table, key, value, 0);
}
