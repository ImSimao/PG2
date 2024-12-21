#ifndef TREENODE_H
#define TREENODE_H

#include "ListNode.h"


typedef struct tNode{ 
    struct tNode *left, *right; 
    char *word;  
    LNode *head; 
} TNode;

void bstAdd(TNode **rootPtr, char *namWord, Book *ref);

void collectNodes(TNode *root, TNode **nodes, int *index);

TNode* buildBalancedTree(TNode **nodes, int start, int end);

void bstBalance(TNode **rootPtr);

LNode *bstSearch(TNode *root, char *namWord);



void bstFree(TNode *root);

#endif