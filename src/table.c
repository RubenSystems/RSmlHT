//
//  table.c
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#include "include/table.h"
#include "include/node.h"

#include <stdlib.h>
#include <string.h>

void * init_table(uint32_t width) {
	void * table_p = calloc(width, sizeof(struct node));
	return table_p;
}

struct node * get_table_node(void * table, KEY_TYPE key) {
	return table + (key * sizeof(struct node));
}
