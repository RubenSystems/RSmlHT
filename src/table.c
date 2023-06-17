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

struct table * init_table(void) {
	struct table * table_p = calloc(1, sizeof(struct table));
	// memset(table_p, 0, sizeof(struct table));
	return table_p;
}

struct node * get_table_node(struct table * table, KEY_TYPE key) {
	return table->data + key;
}
