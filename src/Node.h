#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>

typedef struct node
{
    char *key;
    char *content;
    struct node **childrens;
    int childrensSize;
    struct node *parent;
} Node;

Node *node_new(char *key, char *content);
void node_free(Node *node);
int node_hasParent(Node *node);
int node_hasChildrens(Node *node);
void node_addChildren(Node *node, Node *children);
void node_removeChildren(Node *node, Node *children);

#endif