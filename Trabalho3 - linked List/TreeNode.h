#ifndef TREENODE_H
#define TREENODE_H

#include "ListNode.h"


typedef struct tNode{ 
    struct tNode *left, *right; 
    char *word;  
    LNode *head; 
} TNode;

void printBST(TNode *node, int level);

void bstAdd(TNode **rootPtr, char *namWord, Book *ref);

int countNodes(TNode *root);

TNode *treeToSortedList(TNode *r, TNode *link);

TNode *sortedListToBalancedTree(TNode **listRoot, int n);

void bstBalance(TNode **rootPtr);

LNode *bstSearch(TNode *root, char *namWord);



void bstFree(TNode *root);

#endif