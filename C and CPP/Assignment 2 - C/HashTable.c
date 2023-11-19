#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "HashTable.h"

Element KeyValPCopy(Element elem);
status KeyValPFree(Element elem);
bool KVPCompareByKey(Element elem, Element key);
status PrintKeyValP(Element elem);

Element KeyValPCopy(Element elem){
    if(! elem) return NULL;
    return (KeyValP)elem;
}

status KeyValPFree(Element elem){
    if(! elem) return failure;
    if(DestroyKeyValuePair((KeyValP)elem) != KeyVal_Success) return failure;
    return success;
}

bool KVPCompareByKey(Element elem, Element key){
    if(! elem || ! key) return false;
    KeyValP t_kvp = (KeyValP)elem;
    if(t_kvp == NULL) return false;
    return(IsKeyEqual(t_kvp, (KeyValP)GetKey(key)));
}

status PrintKeyValP(Element elem){
    if(! elem) return failure;
    KeyValP t_kvp = (KeyValP)elem;
    if(t_kvp == NULL) return failure;
    if(DisplayValue(t_kvp) != KeyVal_Success) return failure;
    return success;
}
struct hashTable_s{
    LinkedList* hash_table;
    CopyFunction CopyKey;
    FreeFunction FreeKey;
    PrintFunction PrintKey;
    CopyFunction CopyValue;
    FreeFunction FreeValue;
    PrintFunction PrintValue;
    EqualFunction EqualKey;
    TransformIntoNumberFunction TransformIntoNumber;
    int hashNumber;
};

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if(! copyKey || ! freeKey || ! printKey || ! copyValue || ! freeValue || ! printValue || ! equalKey || ! transformIntoNumber) return NULL;
    hashTable hashT = (hashTable)malloc(sizeof (struct hashTable_s));
    if(! hashT) {
        printf("Memory Problem\n");
        return NULL;
    }
    hashT ->CopyKey = copyKey;
    hashT ->FreeKey = freeKey;
    hashT ->PrintKey = printKey;
    hashT ->CopyValue = copyValue;
    hashT ->FreeValue = freeValue;
    hashT ->PrintValue = printValue;
    hashT ->EqualKey = equalKey;
    hashT ->TransformIntoNumber = transformIntoNumber;
    hashT ->hashNumber = hashNumber;
    hashT -> hash_table = (LinkedList*) calloc(hashT->hashNumber,(sizeof (LinkedList)));
    if(hashT ->hash_table == NULL) {
        free(hashT);
        return NULL;
    }
    for(int i=0; i < hashNumber; i++){
        hashT ->hash_table[i] = CreateLinkedList(KeyValPCopy, KeyValPFree, KVPCompareByKey, PrintKeyValP);
        if(! hashT ->hash_table[i])
          if(destroyHashTable(hashT) == failure) return NULL;
    }
    return hashT;
}

//// The next function gets key and return index to which the value is going to be inserted in the hash table.
static int hash_func(hashTable hashT, int key){
    if(hashT == NULL) return -1;
    int x = hashT ->hashNumber;
    return key % x;
}

status addToHashTable(hashTable hashT, Element key, Element value){
    if(! hashT || ! key || ! value) return failure;
    int n_key = hash_func(hashT, hashT ->TransformIntoNumber(key));
    if(n_key == -1 || hashT ->hashNumber < n_key) return failure;
    KeyValP n_kvp = CreateKeyValuePair(key, value, hashT ->CopyKey, hashT ->FreeKey, hashT->CopyValue,
                                       hashT ->FreeValue, hashT ->EqualKey, hashT ->PrintKey, hashT ->PrintValue);
    if(! n_kvp){
        printf("Memory Problem\n");
        return failure;
    }
    if(AppendNode(hashT -> hash_table[n_key], n_kvp) == List_Failure) //// problem in appending kvp
        return failure;
    return success;
}


Element lookupInHashTable(hashTable hashT, Element key){
    if(! hashT || ! key) return NULL;
    int n_key = hash_func(hashT, hashT ->TransformIntoNumber(key));
    if(n_key == -1 || hashT ->hashNumber < n_key) return NULL;
    int exact_ll_size = GetLengthList(hashT ->hash_table[n_key]);

    for(int i = 1 ; i <= exact_ll_size ; i++){
        KeyValP t_kvp = (KeyValP)(GetDataByIndex(hashT->hash_table[n_key], i));
        if(hashT ->EqualKey(GetKey(t_kvp), key) == true)
            return GetValue(t_kvp);
    }
    return NULL;
}


status removeFromHashTable(hashTable hashT, Element key){
    if(! hashT || ! key) return failure;
    int n_key = hash_func(hashT, hashT ->TransformIntoNumber(key));
    if(n_key == -1 || hashT ->hashNumber < n_key) return failure;
    int exact_ll_size = GetLengthList(hashT ->hash_table[n_key]);
    for(int i = 1 ; i <= exact_ll_size ; i++){
        KeyValP t_kvp = (KeyValP)(GetDataByIndex(hashT->hash_table[n_key], i));
        if(hashT ->EqualKey(GetKey(t_kvp), key) == true){
            if(DeleteNode(hashT->hash_table[n_key], t_kvp) != List_Success) return failure;
            return success;
        }
    }
    return failure;
}

status displayHashElements(hashTable hashT){
    if(! hashT) return failure;
    int hashSize = hashT ->hashNumber;
    for(int i = 0; i < hashSize; i++){
        if(DisplayList(hashT ->hash_table[i]) ==List_Bad_Argument) return failure;
    }
    return success;
}

status destroyHashTable(hashTable hashT){
    if(! hashT) return failure;
    int size = hashT ->hashNumber;
    for(int i = 0 ; i < size ; i++){
        if(DestroyList(hashT ->hash_table[i]) != List_Success)
            return failure;
    }
    free(hashT ->hash_table);
    free(hashT);
    return success;
}