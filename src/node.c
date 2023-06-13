//
//  node.c
//  mlHT
//
//  Created by Ruben Ticehurst-James on 13/06/2023.
//

#include <stdio.h>
#include "include/node.h"


void set_node_data(struct node * n, KEY_TYPE key, VALUE_TYPE value) {
	n->data.value = value;
	n->key	= key;
	n->type	= NODE_DATA;
}

void set_node_pointer(struct node * n, KEY_TYPE key, void * pointer) {
	n->data.pointer = pointer;
	n->key	= key;
	n->type	= NODE_POINTER;
}
