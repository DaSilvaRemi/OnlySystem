#include "node.h"

Node *node_new(char *key, char *content)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("[Error] Can't allocate node");
        return NULL;
    }

    newNode->key = key;
    newNode->content = content;
    newNode->childrens = NULL;
    newNode->childrensSize = 0;
    newNode->parent = NULL;

    return newNode;
}

void node_node_free(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    
    if (hasChildrens(node))
    {
        for (int i = 0; i < node->childrensSize; ++i)
        {
            node_free(node->childrens[i]);
        }
        free(node->childrens);
    }

    free(node);
}

int node_hasParent(Node *node)
{
    return node != NULL && node->parent != NULL ? 1 : 0;
}

int node_hasChildrens(Node *node)
{
    return node != NULL && node->childrensSize > 0 ? 1 : 0;
}

void node_addChildren(Node *node, Node *children)
{
    if (node->childrensSize == 0)
    {
        node->childrens = (Node **)malloc(sizeof(Node **) * node->childrensSize + 1);
    }
    else
    {
        node->childrens = (Node **)realloc(node->childrens, node->childrensSize + 1);
    }

    if (node->childrens == NULL)
    {
        printf("[Error] Failed childrens allocation");
        return;
    }

    node->childrens[node->childrensSize] = children;
    node->childrensSize++;
    children->parent = node;
}

void node_removeChildren(Node *node, Node *children)
{
    int i, j;
    Node *currentChild;

    j = -1;

    for (i = 0; i < node->childrensSize; i++) {
        if (node->childrens[i] == children) {
            j = i;
            break;
        }
    }

    if (j == -1)
    {
        return;
    }

    for (i = j; i < node->childrensSize - 1; i++) {
        node->childrens[i] = node->childrens[i + 1];
    }

    node->childrens = (Node**)realloc(node->childrens, sizeof(Node*) * (node->childrensSize - 1));
    node->childrensSize--;
    node_free(children);
}