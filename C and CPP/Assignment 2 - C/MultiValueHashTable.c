#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"

struct t_MultiVHash{
    hashTable HashTBL;
    CopyFunction copyValFunc;
    FreeFunction  freeValFunc;
    EqualFunction eqalKeyFunc;
    PrintFunction printValFunc;
    PrintFunction printKeyFunc;
};
/// The above function going to be part of the MHTV, because each value in the hash holds LinkedList.

Element copyList(Element element){
    if(! element) return NULL;
    return (LinkedList)element;
}
status freeList(Element element){
    if(! element) return failure;
    if(DestroyList((LinkedList)element) != List_Success) return failure;
    return success;
}

status printList(Element element){
    if(! element) return failure;
    if(DisplayList((LinkedList)element) != List_Success) return failure;
    return success;
}

MultiVHash CreateMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
                                     FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
                                     TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    if (!copyKey || !freeKey || !printKey || !copyValue || !freeValue || !printValue || !equalKey ||
        !transformIntoNumber)
        return NULL;

    MultiVHash MultiVHT = (MultiVHash) malloc(sizeof(struct t_MultiVHash));
    if(MultiVHT == NULL) {
        printf("Memory Problem\n");
        return NULL;
    }
    MultiVHT->HashTBL = createHashTable(copyKey, freeKey, printKey, copyList, freeList,
                                        printList, equalKey, transformIntoNumber, hashNumber);
    MultiVHT ->copyValFunc = copyValue;
    MultiVHT ->freeValFunc = freeValue;
    MultiVHT ->eqalKeyFunc = equalKey;
    MultiVHT ->printValFunc = printValue;
    MultiVHT ->printKeyFunc = printKey;
    if (MultiVHT == NULL) return NULL;
    return MultiVHT;
}

MVHTResult AddToMultiValueHashTable(MultiVHash MultiVH, Element key, Element value){
    if(! MultiVH || ! key || ! value) return MVHT_Bad_Argument;
    if(lookupInHashTable(MultiVH ->HashTBL, key) == NULL) { //// which means there is no such key in the hash table
        LinkedList ls = CreateLinkedList(MultiVH ->copyValFunc, MultiVH ->freeValFunc,
                                         MultiVH ->eqalKeyFunc, MultiVH ->printValFunc);

        if(ls == NULL) return MVHT_Failure;
        if(AppendNode(ls,value) != List_Success) return MVHT_Failure;
        if(addToHashTable(MultiVH ->HashTBL, key, ls) == failure) return MVHT_Failure;
        return MVHT_Success;
    }
    /// In case there are such key already in MVHT, then add to the correct ll.
    if(AppendNode(lookupInHashTable(MultiVH ->HashTBL, key), value) != List_Success) return MVHT_Failure;
    return MVHT_Success;
 }

LinkedList LookupInMultiValueHashTable(MultiVHash MultiVH, Element key){
    if(! MultiVH || ! key) return NULL;
    LinkedList ls = lookupInHashTable(MultiVH->HashTBL, key);
    if(ls == NULL){ /// In case there is no such key in MVHT, the free ll and return NULL.
      if(DestroyList(ls) != List_Success) return NULL;
      return NULL;
    }
    return ls; /// Returns the values ll that match to the key.
}

MVHTResult RemoveFromMultiValueHashTable(MultiVHash MultiVH,Element key, Element value){
    if(! MultiVH || ! key || ! value) return MVHT_Bad_Argument;
    LinkedList ls = LookupInMultiValueHashTable(MultiVH, key);
    if(! ls) return MVHT_Failure;
    if(DeleteNode(ls, value) != List_Success) return MVHT_Failure;
    LinkedList ls_after_del = LookupInMultiValueHashTable(MultiVH, key);
    if(GetLengthList(ls_after_del) == 0) {
        if (removeFromHashTable(MultiVH->HashTBL, key) == failure)
            return failure;
    }
    return MVHT_Success;
}

MVHTResult DisplayMultiValueHashElementsByKey(MultiVHash MultiVH, Element key){
    if(! MultiVH) return MVHT_Bad_Argument;
    Element elem = LookupInMultiValueHashTable(MultiVH, key);
    if(! elem) return MVHT_Failure;
    if(DisplayList((LinkedList)elem) != List_Success) return MVHT_Failure;
    return MVHT_Success;
}

MVHTResult DestroyMultiValueHashTable(MultiVHash MultiVH) {
    if (!MultiVH) return MVHT_Failure;
    if(destroyHashTable(MultiVH ->HashTBL) == failure) return MVHT_Failure;
    free(MultiVH);
    return MVHT_Success;
}