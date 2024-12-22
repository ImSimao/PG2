#include "TreeNode.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void printBST(TNode *node, int level) {
    if (node == NULL) {
        return;
    }

    // Aumenta o nível para a próxima chamada recursiva
    level++;

    // Imprime o filho direito primeiro (para que fique à direita na visualização)
    printBST(node->right, level);

    // Imprime o espaço de indentação
    for (int i = 0; i < level - 1; i++) {
        printf("\t"); // 1 tab espaços para cada nível
    }

    // Imprime o nó atual
    printf("%s\n", node->word);

    // Imprime o filho esquerdo
    printBST(node->left, level);
}


void bstAdd(TNode **rootPtr, char *namWord, Book *ref) {
    // Se a árvore estiver vazia, cria um novo nó
    if (*rootPtr == NULL) {
        *rootPtr = (TNode *)malloc(sizeof(TNode));
        if (*rootPtr == NULL) {
            return; // Memalloc fail
        }
        (*rootPtr)->word = strdup(namWord); // Duplica a string da palavra
        (*rootPtr)->head = NULL; // Inicializa a lista de referências
        (*rootPtr)->left = NULL; // Inicializa o filho esquerdo
        (*rootPtr)->right = NULL; // Inicializa o filho direito
        lRefAdd(&(*rootPtr)->head, ref); // Adiciona a referência do livro
        return;
    }

    // Compara a palavra atual com a palavra a ser inserida
    int cmp = strcmp(namWord, (*rootPtr)->word);
    if (cmp < 0) {
        // A palavra deve ser inserida na subárvore esquerda
        bstAdd(&(*rootPtr)->left, namWord, ref);
    } else if (cmp > 0) {
        // A palavra deve ser inserida na subárvore direita
        bstAdd(&(*rootPtr)->right, namWord, ref);
    } else {
        // A palavra já existe, apenas adiciona a referência do livro
        lRefAdd(&(*rootPtr)->head, ref);
    }
}
// Função para contar o número de nós na árvore
int countNodes(TNode *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Função auxiliar para converter a árvore em uma lista encadeada ordenada
TNode *treeToSortedList(TNode *r, TNode *link) {
    TNode *p;
    if (r == NULL) return link;
    p = treeToSortedList(r->left, r);
    r->left = NULL; // Desconectar o nó da árvore
    r->right = treeToSortedList(r->right, link);
    return p;
}

// Função auxiliar para criar uma árvore balanceada a partir da lista
TNode *sortedListToBalancedTree(TNode **listRoot, int n) {
    if (n == 0) return NULL;
    TNode *leftChild = sortedListToBalancedTree(listRoot, n / 2);
    TNode *parent = *listRoot;
    *listRoot = (*listRoot)->right; // Avançar na lista
    parent->left = leftChild;
    parent->right = sortedListToBalancedTree(listRoot, n - (n / 2 + 1));
    return parent;
}

// Função para balancear a árvore
void bstBalance(TNode **rootPtr) {
    if (rootPtr == NULL || *rootPtr == NULL) return;

    // Passo 1: Converter a árvore em uma lista encadeada ordenada
    TNode *sortedList = NULL;
    sortedList = treeToSortedList(*rootPtr, sortedList);

    // Passo 2: Contar o número de nós
    int nodeCount = countNodes(*rootPtr);

    // Passo 3: Criar uma nova árvore balanceada a partir da lista
    TNode *balancedTree = sortedListToBalancedTree(&sortedList, nodeCount);

    // Atualizar o ponteiro da raiz para a nova árvore balanceada
    *rootPtr = balancedTree;
}

LNode *bstSearch(TNode *root, char *namWord) {
    if (root == NULL) {
        return NULL; // Palavra não encontrada
    }

    int cmp = strcmp(namWord, root->word);
    if (cmp < 0) {
        return bstSearch(root->left, namWord); // Busca na subárvore esquerda
    } else if (cmp > 0) {
        return bstSearch(root->right, namWord); // Busca na subárvore direita
    } else {
        return root->head; // Palavra encontrada, retorna a lista de referências
    }
    if (strstr(root->word, namWord) != NULL) {
        return root->head; // Retorna a lista de referências se for uma substring
    }

}


// Função para libertar a memória ocupada pela árvore
void bstFree(TNode *root) {
    if (root != NULL) {
        bstFree(root->left);  // Liberta a subárvore esquerda
        bstFree(root->right); // Liberta a subárvore direita
        lRefFree(root->head);  // Liberta a lista de referências
        free(root->word);      // Liberta a palavra
        free(root);            // Liberta o nó
    }
}