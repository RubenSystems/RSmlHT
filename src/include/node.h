//
//  node.h
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#ifndef node_h
#define node_h

#include <stdio.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

enum node_type {
	NODE_NOTHING = 0,
	NODE_DATA    = 1,
	NODE_POINTER = 2,
	NODE_OWNER   = 3 // if the node ownes the chunk
};

struct node {
	enum node_type type;
	union {
		struct {
			KEY_TYPE key;
			union {
				VALUE_TYPE     data;
				struct table * pointer;
			} value;
		} format;
		DATA_TYPE raw_data[2];
	} data;
};

void set_node_data(struct node * n, KEY_TYPE key, VALUE_TYPE value);

void set_node_pointer(struct node * n, KEY_TYPE key, void * pointer);

#ifdef __cplusplus
}
#endif

#endif /* node_h */
