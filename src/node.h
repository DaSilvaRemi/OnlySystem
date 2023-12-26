#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

typedef enum nodeType
{
    DIRECTORY_T,
    FILE_T
} NodeType;

typedef struct nodeData
{
    char *key;
    char *content;
    int keyLength;
    int contentLength;
    NodeType nodeType;
} NodeData;

typedef struct node
{
    NodeData data;
    LinkedList *childrens;
    struct node *parent;
} Node;

Node *node_new(NodeData data);
void node_free(Node *node);
int node_hasParent(Node *node);
int node_hasChildrens(Node *node);
void node_addChildren(Node *node, Node *children);
void node_removeChildren(Node *node, Node *children);

#endif
