//
// Created by victor on 12/14/22.
//

#ifndef HW_3_KEYVALUEPAIR_H
#define HW_3_KEYVALUEPAIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct t_KeyValP *KeyValP;
typedef enum{KeyVal_Is_Empty, KeyVal_Bad_Argument, KeyVal_Success, KeyVal_Failure} KeyValResult;

/*
 * Define all the function that going to be implemented:
 */
//
KeyValP CreateKeyValuePair(Element key, Element value, CopyFunction CopyKeyFunc, FreeFunction FreeKeyFunc, CopyFunction CopyValFunc, FreeFunction FreeValFunc, EqualFunction EqualFunc,PrintFunction PrintKeyFunc, PrintFunction PrintValFunc);
//
KeyValResult DestroyKeyValuePair(KeyValP kvp);
//
KeyValResult DisplayValue(KeyValP kvp);
//
KeyValResult DisplayKey(KeyValP kvp);
//
Element GetValue(KeyValP kvp);
//
Element GetKey(KeyValP kvp);
//
bool IsKeyEqual(KeyValP kvp, Element elem);
//
#endif //HW_3_KEYVALUEPAIR_H
