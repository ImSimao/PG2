#include "TreeNode.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void bstAdd(TNode **rootPtr, char *namWord, Book *ref) {
    // Se a árvore estiver vazia, cria um novo nó
    if (*rootPtr == NULL) {
        *rootPtr = (TNode *)malloc(sizeof(TNode));
        if (*rootPtr == NULL) {
            return; // Falha na alocação de memória
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

// Função auxiliar para coletar nós em ordem
void collectNodes(TNode *root, TNode **nodes, int *index) {
    if (root == NULL) {
        return;
    }
    collectNodes(root->left, nodes, index); // Visita a subárvore esquerda
    nodes[(*index)++] = root; // Adiciona o nó atual ao vetor
    collectNodes(root->right, nodes, index); // Visita a subárvore direita
}

// Função auxiliar para construir uma árvore balanceada a partir de um vetor
TNode *buildBalancedTree(TNode **nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2; // Encontra o meio do vetor
    TNode *node = nodes[mid]; // O nó do meio se torna a raiz da subárvore
    node->left = buildBalancedTree(nodes, start, mid - 1); // Constrói a subárvore esquerda
    node->right = buildBalancedTree(nodes, mid + 1, end); // Constrói a subárvore direita
    return node;
}

// Função principal para balancear a árvore
void bstBalance(TNode **rootPtr) {
    if (*rootPtr == NULL) {
        return; // Se a árvore estiver vazia, não faz nada
    }

    // Coleta todos os nós em um vetor
    int size = 0;
    TNode *nodes[1000]; // Supondo que a árvore não terá mais de 1000 nós
    collectNodes(*rootPtr, nodes, &size);

    // Reconstrói a árvore balanceada
    *rootPtr = buildBalancedTree(nodes, 0, size - 1);
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
}


// Função para liberar a memória ocupada pela árvore
void bstFree(TNode *root) {
    if (root != NULL) {
        bstFree(root->left);  // Libera a subárvore esquerda
        bstFree(root->right); // Libera a subárvore direita
        lRefFree(root->head);  // Libera a lista de referências
        free(root->word);      // Libera a palavra
        free(root);            // Libera o nó
    }
}