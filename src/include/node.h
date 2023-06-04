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
	NODE_DATA = 1,
	NODE_POINTER = 2
};

struct node {
	enum node_type type;
	KEY_TYPE key;
	VALUE_TYPE data;
};
	
#ifdef __cplusplus
}
#endif

#endif /* node_h */
