#include "tree.h"

Tree *tree_new()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    
    if (tree == NULL)
    {
        printf("[Error] Can't allocate a new tree");
        return NULL;
    }

    tree->root = NULL;

    return tree;
}

void tree_free(Tree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->root)
    {
        node_free(tree->root);
    }

    free(tree);
}

void tree_addNode(Tree *tree, Node *parent, Node *newNode)
{
    if (tree->root == NULL)
    {
        tree->root = newNode;
    }
    else if (parent)
    {
        node_addChildren(parent, newNode);
    }
}

void tree_removeNode(Tree *tree, Node *node)
{
    if (node == NULL)
    {
        return;
    }
    

    if (node_hasParent(node))
    {
        node_removeChildren(node->parent, node);
    }
    else if (node == tree->root)
    {
        node_free(tree->root);
        tree->root = NULL;
    }
}

LinkedList *tree_getReversePreorder(Node *node)
{
    Node *current;
    LinkedList *reversePrefix = NULL;

    reversePrefix = linkedList_new();
    current = node;

    while (current != NULL)
    {
       linkedList_add(reversePrefix, (void *)current);
       current = current->parent;
    }

    return reversePrefix;
}

LinkedList* tree_getPreorder(Node* node){
    LinkedList* preorderLinkedList;
    
    preorderLinkedList = linkedList_new();
    tree_getPreorderRecursive(node, preorderLinkedList);

    return preorderLinkedList;
}

void tree_getPreorderRecursive(Node* node, LinkedList* preorderLinkedList){
    if (node == NULL)
    {
        return;
    }

    ListNode* current;

    current = node->childrens->head;

    linkedList_add(preorderLinkedList, (void*) node);

    while (current != NULL)
    {
        tree_getPreorderRecursive((Node *) current->node, preorderLinkedList);
        current = current->next;
    }
}

LinkedList* tree_getPostorder(Node* node){
    LinkedList* postOrderLinkedList;
    
    postOrderLinkedList = linkedList_new();
    tree_getPostorderRecursive(node, postOrderLinkedList);

    return postOrderLinkedList;
}

void tree_getPostorderRecursive(Node* node, LinkedList* postOrderLinkedList){
    if (node == NULL)
    {
        return;
    }

    ListNode* current;

    current = node->childrens->head;

    while (current != NULL)
    {
        tree_getPostorderRecursive((Node *) current->node, postOrderLinkedList);
        current = current->next;
    }

    linkedList_add(postOrderLinkedList, (void*) node);
}