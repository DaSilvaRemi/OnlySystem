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
    newNode->childrens = linkedList_new();
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
    while (current != NULL)
    {
        ListNode* next = current->next;
        node_free((Node*) current->node);
        current = next;
    }

    linkedList_free(node->childrens);

    if (node->data.content != NULL)
    {
        free(node->data.content);
    }

    if (node->data.key != NULL)
    {
        free(node->data.key);
    }
    
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
    children->parent = node;
}

Node* node_findChildrenWithKey(Node *node, char* key){
    ListNode *current;
    int i;

    current = node->childrens->head;

    while (current != NULL)
    {
        if (strcmp(((Node*) current->node)->data.key, key) == 0)
        {
            return (Node*) current->node;
        }

        current = current->next;
    }
    
    return NULL;
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