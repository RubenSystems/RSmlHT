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

void * init_table(uint32_t width);

struct node * get_table_node(void *, KEY_TYPE);

#ifdef __cplusplus
}
#endif

#endif /* table_h */
