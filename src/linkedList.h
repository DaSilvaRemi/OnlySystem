#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "listNode.h"

typedef struct linkedList {
    ListNode* head;
    ListNode* tail;
    int counts;
} LinkedList ;

LinkedList* linkedList_new();
ListNode* linkedList_findNode(LinkedList* list, void* node);
void linkedList_add(LinkedList* list, void* node);
void linkedList_del(LinkedList *list, ListNode* node);
void linkedList_free(LinkedList* list);
void linkedList_reverse(LinkedList* list);

#endif
