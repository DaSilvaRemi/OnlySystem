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
    if (!tree->root)
    {
        tree->root = newNode;
    }
    else if (parent)
    {
        node_addChildren(parent, newNode);
        newNode->parent = parent;
    }
}

void tree_removeNode(Tree *tree, Node *node)
{
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

LinkedList *tree_getReversePrefix(Node *node)
{
    Node *current;
    LinkedList *reversePrefix;

    reversePrefix = linkedList_new();
    current = node;

    do
    {
        linkedList_add(reversePrefix, (void *)current);
        current = node->parent;
    } while (current != NULL);

    return reversePrefix;
}