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

#define DATA_TYPE	    uint64_t
#define KEY_TYPE	    DATA_TYPE
#define VALUE_TYPE	    DATA_TYPE

#define INITIAL_TABLE_WIDTH 5
#define TABLE_SIZE(WIDTH)   (2 << WIDTH)
#define TABLE_WIDTH	    INITIAL_TABLE_WIDTH
#define TABLE_WIDTH_MASK    (1 << (TABLE_WIDTH + 1)) - 1

#define ARM		    0

#ifdef __cplusplus
}
#endif

#endif /* config_h */
