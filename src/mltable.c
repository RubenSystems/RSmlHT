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


static void __create_until_nonequal(uint64_t key, uint32_t layer, struct node * ret, uint64_t value) {
	struct node * current_ret = ret;
	void * new_table = NULL;
	size_t lk1, lk2;
	// in english: layer key for the inserted node == layer key for the current node.
	while ((lk1 = __layer_key(key, layer)) == (lk2 = __layer_key(ret->key, layer))) {
		layer += 1;
		new_table = init_table(TABLE_SIZE(TABLE_WIDTH(layer)));
		set_node_pointer(current_ret, 0, new_table);
		current_ret = get_table_node(new_table, lk1);
	}
	// now both layer keys are !=
	struct node * fl_new = get_table_node(new_table, lk1);
	set_node_data(fl_new, key, value);
	
	struct node * fl_current = get_table_node(new_table, lk2);
	set_node_data(fl_current, ret->key, ret->data.value);
}

static void __set_helper(void * table, KEY_TYPE key, VALUE_TYPE value, uint32_t layer) {
	struct node * ret;
	bool	      selection = true;
	while (selection) {
		ret = get_table_node(table, __layer_key(key, layer));

		switch (ret->type) {
			case NODE_NOTHING: {
				set_node_data(ret, key, value);
				selection	= false;
			} break;
			case NODE_DATA: {
				if (equatable(key, ret->key)) {
					ret->data.value = value;
				} else {
					__create_until_nonequal(key, layer, ret, value);
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
