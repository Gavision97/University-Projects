//
// Created by victor on 12/17/22.
//

#ifndef HW_3_MULTIVALUEHASHTABLE_H
#define HW_3_MULTIVALUEHASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "HashTable.h"

typedef struct t_MultiVHash* MultiVHash;
typedef enum t_MVHTResult{MVHT_Is_Empty, MVHT_Bad_Argument, MVHT_Success, MVHT_Failure}MVHTResult;

MultiVHash CreateMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                                     EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber,
                                     int hashNumber);
//
MVHTResult DestroyMultiValueHashTable(MultiVHash MultiVH);
//
MVHTResult AddToMultiValueHashTable(MultiVHash MultiVH, Element key, Element value);
//
LinkedList LookupInMultiValueHashTable(MultiVHash MultiVH, Element key);
//
MVHTResult RemoveFromMultiValueHashTable(MultiVHash MultiVH, Element key, Element value);
//
MVHTResult DisplayMultiValueHashElementsByKey(MultiVHash MultiVH, Element key);
//

#endif //HW_3_MULTIVALUEHASHTABLE_H
