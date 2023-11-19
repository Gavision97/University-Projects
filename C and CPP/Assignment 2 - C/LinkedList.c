#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"

typedef struct t_Node{
    Element data;
    struct t_Node* next;
}Node;

struct t_LinkedList{
    CopyFunction CopyFunc;
    FreeFunction FreeFunc;
    EqualFunction EqualFunc;
    PrintFunction PrintFunc;
    Node* head;
    Node* tail;
    int size;
};

LinkedList CreateLinkedList(CopyFunction CopyFunc, FreeFunction FreeFunc, EqualFunction EqualFunc, PrintFunction PrintFunc){
    LinkedList list = (LinkedList) malloc(sizeof (struct t_LinkedList));
    if(! list) {
        printf("Memory Problem\n");
        return NULL;
    }
    list ->EqualFunc = EqualFunc;
    list ->CopyFunc = CopyFunc;
    list ->FreeFunc = FreeFunc;
    list ->PrintFunc = PrintFunc;
    list ->head = NULL;
    list ->tail = NULL;
    list -> size = 0;
}
ListResult AppendNode(LinkedList list, Element elem){
    if(elem == NULL) return List_Failure;
    Element new_elem = list ->CopyFunc(elem);
    if(list ->head == NULL){
        list ->head = malloc(sizeof(Node));
        if(list ->head == NULL) {
            printf("Memory Problem\n");
            return List_Failure;
        }

        list ->head ->data = new_elem;
        list ->head ->next =NULL;
        list ->tail = list ->head;
        list ->size ++;
        return List_Success;
    }
    list ->tail ->next = malloc(sizeof(Node));
    if(list -> tail -> next == NULL){
        printf("Memory Problem\n");
        return List_Failure;
    }
    list ->tail= list ->tail ->next;
    list ->tail ->data = new_elem;
    list ->tail ->next = NULL;
    list ->size ++;
    return List_Success;
}

ListResult  DeleteNode(LinkedList list, Element elem) {
    if (list->size == 0) return List_Is_Empty;
    if(list->EqualFunc(GetDataByIndex(list, list ->size), elem) && GetLengthList(list) > 1){ //// last elem
        Node* runner = list ->head;
        Node* prev = NULL;
        while (runner ->next){
            prev = runner;
            runner = runner->next;
        }
        prev ->next =NULL;
        list ->tail = prev;
        list ->FreeFunc(runner ->data);
        free(runner);
        list ->size --;
        return List_Success;
    }
    if (elem == NULL) return List_Bad_Argument;
    Node *runner = list ->head;
    if(list ->EqualFunc(runner ->data, elem)){
        list ->head = list ->head ->next;
        list ->FreeFunc(runner ->data);
        free(runner);
        list ->size--;
        return List_Success;
    }
    runner = runner ->next;
    Node* prev = list ->head;
    while(runner != NULL){
        if(list ->EqualFunc(runner ->data,elem)){
            list ->FreeFunc(runner ->data);
            prev ->next = runner ->next;
            free(runner);
            list -> size --;
            return List_Success;
        }
        prev = runner;
        runner = runner -> next;
    }
    return List_Failure;
}
ListResult DisplayList(LinkedList list){
    if(! list) return List_Bad_Argument;
    if(list -> size == 0) return List_Failure;
    Node* runner = list -> head;
    while(runner){
        list -> PrintFunc(runner ->data);
        runner = runner -> next;
    }
    return List_Success;
}

Element GetDataByIndex(LinkedList list, int index){
    if(list -> size == 0) return NULL;
    if(index > list ->size || index < 1) return NULL;
    int itr = 1;
    Node* runner = list ->head;
    while(itr != index){
        runner = runner ->next;
        itr++;
    }
    Element t_elem = list ->CopyFunc(runner ->data);
    if(! t_elem) return NULL;
    return t_elem;
}

int GetLengthList(LinkedList list){
    if(list == NULL) return -1;
    return list ->size;
}
Element SearchByKeyInList(LinkedList list, Element elem){
    if(elem == NULL || list == NULL || list ->size == 0) return NULL;
    Element t_elem = list -> CopyFunc(elem);
    if(! t_elem) return NULL;
    Node* runner = list -> head;

    while(runner){
        if(list ->EqualFunc(runner ->data, t_elem) == true) return t_elem;
        runner = runner ->next;
    }
    return NULL;
}
ListResult DestroyList(LinkedList list){
    if(! list) return List_Bad_Argument;
    if(list ->head == NULL){
        free(list);
        return List_Success;
    }
    Node* runner = list ->head;
    Node* prev = list -> head;
    while(runner){
        list ->FreeFunc(runner ->data);
        runner = runner -> next;
        free(prev);
        prev = runner;
    }
    free(list);
    return List_Success;
}