//
//  node.c
//  mlHT
//
//  Created by Ruben Ticehurst-James on 13/06/2023.
//

#include <stdio.h>

#include "include/node.h"



#if ARM
#include <arm_neon.h>
static void
__mov2_64(const DATA_TYPE * key, const DATA_TYPE * value, DATA_TYPE * dest) {
	int64x1_t data1		= vld1_u64(key);
	int64x1_t data2		= vld1_u64(value);
	int64x2_t data_combined = vcombine_u64(data1, data2);
	vst1q_u64(dest, data_combined);
}
#endif

void set_node_data(struct node * n, const KEY_TYPE key, const VALUE_TYPE value) {
#if ARM
	__mov2_64(&key, &value, n->data.raw_data);

#else

	n->data.format.value.data    = value;
	n->data.format.key	     = key;
#endif

	n->type = NODE_DATA;
}

void set_node_pointer(struct node * n, KEY_TYPE key, void * pointer) {
#if ARM
	__mov2_64(&key, ( VALUE_TYPE * )&pointer, n->data.raw_data);
	// int64x1_t data1 = vld1_u64(&key);
	// int64x1_t data2 = vld1_u64((VALUE_TYPE*)&pointer);
	// int64x2_t data_combined = vcombine_u64(data1, data2);
	// vst1q_u64(n->data.raw_data, data_combined);

#else
	n->data.format.value.pointer = pointer;
	n->data.format.key	     = key;
#endif

	n->type = NODE_POINTER;
}
