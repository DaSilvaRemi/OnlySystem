#ifndef __LIST_NODE_H__
#define __LIST_NODE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
    void* node;
    struct listNode* next;
    struct listNode* prev;
} ListNode;

ListNode* listNode_new(void* node);
void listNode_free(ListNode* node);

#endif
