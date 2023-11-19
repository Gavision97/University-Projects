#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeyValuePair.h"
struct t_KeyValP{
    CopyFunction CopyKeyFunc;
    FreeFunction FreeKeyFunc;
    CopyFunction CopyValFunc;
    FreeFunction FreeValFunc;
    EqualFunction EqualFunc;
    PrintFunction PrintKeyFunc;
    PrintFunction PrintValFunc;
    Element key;
    Element value;
};

KeyValP CreateKeyValuePair(Element k, Element v, CopyFunction CopyKeyFunc, FreeFunction FreeKeyFunc, CopyFunction CopyValFunc, FreeFunction FreeValFunc, EqualFunction EqualFunc, PrintFunction PrintKeyFunc, PrintFunction PrintValFunc){
    KeyValP kvp = (KeyValP)malloc(sizeof(struct t_KeyValP));
    if(! kvp) {
        printf("Memory Problem\n");
        return NULL;
    }
    kvp ->CopyKeyFunc = CopyKeyFunc;
    kvp ->FreeKeyFunc = FreeKeyFunc;
    kvp ->CopyValFunc = CopyValFunc;
    kvp ->FreeValFunc = FreeValFunc;
    kvp ->EqualFunc = EqualFunc;
    kvp ->PrintKeyFunc = PrintKeyFunc;
    kvp ->PrintValFunc = PrintValFunc;
    kvp ->key = k;
    kvp ->value = v;
    return kvp;
}

KeyValResult DisplayValue(KeyValP kvp){
    if(! kvp) return KeyVal_Bad_Argument;
    kvp ->PrintValFunc(kvp ->value);
    return KeyVal_Success;
}

KeyValResult DisplayKey(KeyValP kvp){
    if(! kvp) return KeyVal_Bad_Argument;
    kvp ->PrintKeyFunc(kvp ->key);
    return KeyVal_Success;
}

Element GetValue(KeyValP kvp){
    if(! kvp) return NULL;
    Element t_elem = kvp ->CopyValFunc(kvp ->value);
    if(! t_elem) return NULL;
    return t_elem;
}

Element GetKey(KeyValP kvp){
    if(! kvp) return NULL;
    Element t_elem = kvp ->CopyKeyFunc(kvp ->key);
    if(! t_elem) return NULL;
    return t_elem;
}

bool IsKeyEqual(KeyValP kvp, Element elem){
    if(! elem || ! kvp) return false;
    return(kvp ->EqualFunc(kvp ->key, elem));
}

KeyValResult DestroyKeyValuePair(KeyValP kvp){
    if(! kvp) return KeyVal_Bad_Argument;
    kvp ->FreeKeyFunc(kvp ->key);
    kvp ->FreeValFunc(kvp ->value);
    free(kvp);
    return KeyVal_Success;
}