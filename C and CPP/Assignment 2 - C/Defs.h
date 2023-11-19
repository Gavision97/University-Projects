//
// Created by victor on 12/13/22.
//

#ifndef HW_3_DEFS_H
#define HW_3_DEFS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_bool {false, true} bool;
typedef enum e_status {success =1 , failure = -1} status;

typedef void* Element;

typedef Element (*CopyFunction)(Element);
typedef status (*FreeFunction)(Element);
typedef status (*PrintFunction)(Element);
typedef  int (*TransformIntoNumberFunction)(Element);
typedef bool(*EqualFunction)(Element, Element);

#endif //HW_3_DEFS_H
