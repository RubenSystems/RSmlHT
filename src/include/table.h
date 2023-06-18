//
//  table.h
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#ifndef table_h
#define table_h

#include <stdint.h>
#include "node.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct table {
	struct node data[TABLE_SIZE(TABLE_WIDTH)];
};

// struct table * init_table(void);

struct node * get_table_node(struct table *, KEY_TYPE);

#ifdef __cplusplus
}
#endif

#endif /* table_h */
