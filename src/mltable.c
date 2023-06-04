//
//  mltable.c
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#include "include/mltable.h"
#include "include/table.h"

#include <stdbool.h>

// width is 2<<6 (128)
#define TABLE_WIDTH 6
#define TABLE_WIDTH_MASK (1 << TABLE_WIDTH) - 1


struct mltable init_mltable(void) {
	struct mltable ret = {
		init_table(2 << TABLE_WIDTH),
		0
	};
	return ret;
}


static size_t __layer_key(KEY_TYPE key, uint32_t layer) {
	return TABLE_WIDTH_MASK & (key >> (layer * TABLE_WIDTH));
}

struct node * mltable_get(void * table, KEY_TYPE key) {
	struct node * ret;
	int layer = 0;
	
	while (1) {
		ret = get_table_node(table, __layer_key(key, layer++));
		if (ret->type == NODE_POINTER) {
			table = (void *)ret->data;
		} else {
			break; 
		}
	};
	
	return ret;
}

static bool equatable(KEY_TYPE a, KEY_TYPE b){
	return a == b;
}


static void __set_helper(void * table, KEY_TYPE key, VALUE_TYPE value, uint32_t layer) {
	struct node * ret;
	
	while (1) {
		ret = get_table_node(table, __layer_key(key, layer));
		if (ret->type == NODE_POINTER) {
			table = (void *)ret->data;
			continue;
		} else if (ret->type == NODE_DATA && !equatable(ret->key, key)) {
			void * new_table = init_table(TABLE_WIDTH);
			__set_helper(new_table, ret->key, ret->data, layer + 1);
			__set_helper(new_table, key, value, layer + 1);
			ret->key = 0;
			ret->data = (uintptr_t)new_table;
			ret->type = NODE_POINTER;
		} else if (ret->type == NODE_DATA) {
			ret->data = value;
		} else {
			ret->data = value;
			ret->key = key;
		}
		return;
	}
}

void mltable_set(void * table, KEY_TYPE key, VALUE_TYPE value) {
	__set_helper(table, key, value, 0);
}
