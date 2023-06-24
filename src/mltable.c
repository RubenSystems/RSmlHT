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

struct mltable init_mltable(struct sc_alloc * allocator) {
	struct mltable ret;
	ret.count     = 0;
	ret.root      = &allocator->root;
	ret.allocator = allocator;
	return ret;
}

static size_t __layer_key(KEY_TYPE key, uint32_t layer) {
	return TABLE_WIDTH_MASK & (key >> (layer * TABLE_WIDTH));
}

struct node * mltable_get(struct table * table, KEY_TYPE key) {
	struct node * ret   = NULL;
	int	      layer = 0;

	while (1) {
		ret = get_table_node(table, __layer_key(key, layer++));
		if (ret->type != NODE_POINTER) {
			break;
		}
		table = ret->data.format.value.pointer;
	};

	return ret;
}

static inline bool equatable(KEY_TYPE a, KEY_TYPE b) {
	return a == b;
}

static void __create_until_nonequal(
	struct mltable * mltable, uint64_t key, uint32_t layer, size_t lk1,
	struct node * current_ret, uint64_t value
) {
	KEY_TYPE       replacement_key	 = current_ret->data.format.key;
	VALUE_TYPE     replacement_value = current_ret->data.format.value.data;
	struct table * new_table	 = NULL;
	size_t	       lk2;
	// layer key for the inserted node == layer key for the current node.
	do {
		layer += 1;
		// new_table = init_table();
		new_table = allocate(mltable->allocator);
		set_node_pointer(current_ret, 0, new_table);
		current_ret = get_table_node(
			new_table, (lk1 = __layer_key(key, layer))
		);

	} while (lk1 == (lk2 = __layer_key(replacement_key, layer)));
	set_node_data(current_ret, key, value);

	struct node * fl_current = get_table_node(new_table, lk2);
	set_node_data(fl_current, replacement_key, replacement_value);
}

static void __set_helper(
	struct mltable * mltable, KEY_TYPE key, VALUE_TYPE value, uint32_t layer
) {
	struct table * table = mltable->root;
	struct node *  ret;
	bool	       selection = true;
	size_t	       layer_key;
	while (selection) {
		ret = get_table_node(
			table, (layer_key = __layer_key(key, layer))
		);

		switch (ret->type) {
		case NODE_NOTHING: {
			set_node_data(ret, key, value);
			selection = false;
		} break;
		case NODE_DATA: {
			if (equatable(key, ret->data.format.key)) {
				ret->data.format.value.data = value;
			} else {
				__create_until_nonequal(
					mltable, key, layer, layer_key, ret,
					value
				);
			}
			selection = false;
		} break;
		case NODE_POINTER: {
			table = ret->data.format.value.pointer;
			layer++;
		} break;
		default: {
			printf("[TABLE] - broken layer: %i | mapping %llu -> %llu \n",
			       layer, key, value);
			exit(-1);
		}
		}
	}
}

void mltable_set(struct mltable * mltable, KEY_TYPE key, VALUE_TYPE value) {
	__set_helper(mltable, key, value, 0);
}
