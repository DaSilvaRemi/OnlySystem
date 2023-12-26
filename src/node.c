#include "node.h"

Node *node_new(NodeData data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("[Error] Can't allocate node");
        return NULL;
    }

    newNode->data = data;
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

    ListNode *current = node->childrens->head;
    while (current)
    {
        ListNode *next = current->next;
        node_free((Node*) next->node);
        current = next;
    }

    linkedList_free(node->childrens);

    free(node);
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
    linkedList_add(node->childrens, (void*) children);
}

void node_removeChildren(Node *node, Node *children)
{
   ListNode* childrenListNode;
   childrenListNode = linkedList_findNode(node->childrens, (void*) children);

   if (childrenListNode == NULL)
   {
        printf("Children not found !");
        return;
   }

   node_free(children);
   linkedList_del(node->childrens, childrenListNode);
}