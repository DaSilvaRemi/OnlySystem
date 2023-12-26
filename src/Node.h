#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
    struct node* node;
    struct listNode* next;
    struct listNode* prev;
} ListNode;

typedef struct linkedList {
    ListNode* head;
    ListNode* tail;
    int counts;
} LinkedList ;

typedef struct node
{
    char *key;
    char *content;
    LinkedList* childrens;
    struct node *parent;
} Node;

Node *node_new(char *key, char *content);
void node_free(Node *node);
void node_freeChild(ListNode *child);
void node_freeChildrens(LinkedList *childrens);
int node_hasParent(Node *node);
int node_hasChildrens(Node *node);
void node_addChildren(Node *node, Node *children);
void node_removeChildren(Node *node, ListNode *children);

#endif