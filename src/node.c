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
    newNode->childrens = (LinkedList *)malloc(sizeof(LinkedList));
    newNode->parent = NULL;

    return newNode;
}

void node_free(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    node_freeChildrens(node->childrens);

    free(node);
}

void node_freeChild(ListNode *child)
{
    if (child == NULL)
    {
        return;
    }

    free(child);
}

void node_freeChildrens(LinkedList *childrens)
{
    if (childrens == NULL)
    {
        return;
    }

    ListNode *current = childrens->head;
    while (current)
    {
        ListNode *next = current->next;
        node_freeChild(current);
        current = next;
    }

    free(childrens);
}

int node_hasParent(Node *node)
{
    return node != NULL && node->parent != NULL ? 1 : 0;
}

int node_hasChildrens(Node *node)
{
    return node != NULL && node->childrens->counts > 0 ? 1 : 0;
}

void node_addChildren(Node *node, Node *children)
{
    ListNode *newListNode = (ListNode *)malloc(sizeof(ListNode));

    if (newListNode != NULL)
    {
        printf("[Error] Can't allocate new list node");
        return;
    }

    newListNode->next = NULL;
    newListNode->prev = NULL;
    newListNode->node = node;

    if (node->childrens->counts == 0)
    {
        node->childrens->head = newListNode;
        node->childrens->tail = newListNode;
    }
    else
    {
        node->childrens->tail->next = newListNode;
        newListNode->prev = node->childrens->tail;
        node->childrens->tail = newListNode;
    }

    node->childrens->counts++;
}

void node_removeChildren(Node *node, ListNode *children)
{
    ListNode *current;
    int i;

    current = node->childrens->head;

    for (i = 0; i < node->childrens->counts; i++)
    {
        if (current == children)
        {
            break;
        }
    }

    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else
    {
        node->childrens->head = current->next;
    }

    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }
    else
    {
        node->childrens->tail = current->prev;
    }

    node_freeChild(current);
    node->childrens->counts--;
}