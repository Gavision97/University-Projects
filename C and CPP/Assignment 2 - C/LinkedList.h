//
// Created by victor on 12/13/22.
//
#ifndef HW_3_LINKEDLIST_H
#define HW_3_LINKEDLIST_H
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct t_LinkedList *LinkedList;
typedef enum t_ListResult{List_Is_Empty, List_Bad_Argument, List_Success, List_Failure} ListResult;

//// NOTE : The first index of the LinkedList is 1 and not 0 !!
/*
 * Define all the function that going to be implemented:
 */
//
LinkedList CreateLinkedList(CopyFunction CopyFunc, FreeFunction FreeFunc, EqualFunction EqualFunc, PrintFunction PrintFunc);
//
ListResult DestroyList(LinkedList list);
//
ListResult AppendNode(LinkedList list, Element elem);
//
ListResult DeleteNode(LinkedList list, Element elem);
//
ListResult DisplayList(LinkedList list);
//
Element GetDataByIndex(LinkedList list, int index);
//
int GetLengthList(LinkedList list);
//
Element SearchByKeyInList(LinkedList list, Element elem);
//

#endif //HW_3_LINKEDLIST_H