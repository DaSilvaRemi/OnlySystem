#include "listNode.h"

ListNode* listNode_new(void* node){
    ListNode* newListNode = (ListNode*)malloc(sizeof(ListNode));

    if (newListNode == NULL) {
        printf("[Error] Can't allocate new list node");
        return NULL;
    }

    newListNode->next = NULL;
    newListNode->prev = NULL;
    newListNode->node = node;

    return newListNode;
}

void listNode_free(ListNode* listNode) {
    if (listNode == NULL)
    {
        return;
    }

    free(listNode);
}