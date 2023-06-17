//
//  config.h
//  mlHT
//
//  Created by Ruben Ticehurst-James on 30/05/2023.
//

#ifndef config_h
#define config_h

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_TYPE   uint64_t
#define VALUE_TYPE uint64_t
	
#define INITIAL_TABLE_WIDTH	4
#define TABLE_SIZE(WIDTH)	(2 << WIDTH)
#define TABLE_WIDTH	INITIAL_TABLE_WIDTH
#define TABLE_WIDTH_MASK (1 << (TABLE_WIDTH + 1)) - 1


#ifdef __cplusplus
}
#endif

#endif /* config_h */
