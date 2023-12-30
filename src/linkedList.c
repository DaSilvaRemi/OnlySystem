#include "linkedList.h"

LinkedList *linkedList_new()
{
    LinkedList *newList = (LinkedList *)malloc(sizeof(LinkedList));

    if (newList == NULL)
    {
        printf("[Error] Can't allocate linked list");
        return NULL;
    }

    newList->head = NULL;
    newList->tail = NULL;
    newList->counts = 0;

    return newList;
}

ListNode *linkedList_findNode(LinkedList *list, void *node)
{
    ListNode *current;
    int i;

    current = list->head;

    while (current != NULL)
    {
        if (current->node == node)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void linkedList_add(LinkedList *list, void *node)
{
    ListNode *newListNode;

    newListNode = listNode_new(node);

    if (list->counts == 0)
    {
        list->head = newListNode;
        list->tail = newListNode;
    }
    else
    {
        list->tail->next = newListNode;
        newListNode->prev = list->tail;
        list->tail = newListNode;
    }

    list->counts++;
}

void linkedList_del(LinkedList *list, ListNode *listNode)
{
    ListNode *current;
    current = linkedList_findNode(list, listNode->node);

    if (current == NULL)
    {
        printf("Node not found !");
        return;
    }

    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else
    {
        list->head = current->next;
    }

    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }
    else
    {
        list->tail = current->prev;
    }

    listNode_free(current);
    list->counts--;
}

void linkedList_free(LinkedList *list)
{
    if (list == NULL)
    {
        return;
    }

    ListNode *current = list->head;
    while (current != NULL)
    {
        ListNode* next = current->next;
        listNode_free(current);
        current = next;
    }
    
    free(list);
}

void linkedList_reverse(LinkedList *list)
{
    if (list == NULL)
    {
        return;
    }

    ListNode *current = list->head;
    ListNode *temp = NULL;

    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}
