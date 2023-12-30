#ifndef __Tree_H__
#define __Tree_H__

#include "node.h"

typedef struct tree
{
    Node* root;
} Tree;

Tree* tree_new();
void tree_free(Tree* tree);
void tree_addNode(Tree* tree, Node* parent, Node* newNode);
void tree_removeNode(Tree* tree, Node* node);

LinkedList* tree_getReversePreorder(Node* node);
LinkedList* tree_getPostorder(Node* node);
void tree_getPostorderRecursive(Node* node, LinkedList* postOrderLinkedList);

#endif
