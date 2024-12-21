#include "TreeNode.h"
#include <stdlib.h>
#include <string.h>



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


// Função auxiliar para coletar os nós em uma lista
void collectNodes(TNode *root, TNode **nodes, int *index) {
    if (root == NULL) {
        return;
    }
    // Coleta os nós da subárvore esquerda
    collectNodes(root->left, nodes, index);
    // Adiciona o nó atual à lista
    nodes[(*index)++] = root;
    // Coleta os nós da subárvore direita
    collectNodes(root->right, nodes, index);
}

// Função auxiliar para construir uma árvore balanceada a partir da lista de nós
TNode* buildBalancedTree(TNode **nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2; // Encontra o ponto médio
    TNode *node = nodes[mid];    // O nó do meio se torna a raiz da subárvore
    // Constrói a subárvore esquerda e direita
    node->left = buildBalancedTree(nodes, start, mid - 1);
    node->right = buildBalancedTree(nodes, mid + 1, end);
    return node;
}

// Função para balancear a árvore
void bstBalance(TNode **rootPtr) {
    if (*rootPtr == NULL) {
        return; // Se a árvore estiver vazia, não faz nada
    }

    // Coleta todos os nós da árvore em um array
    int size = 0;
    TNode **nodes = (TNode **)malloc(sizeof(TNode *) * 1000); // Alocação inicial
    if (nodes == NULL) {
        return; // Falha na alocação de memória
    }

    collectNodes(*rootPtr, nodes, &size);

    // Libera a memória da árvore antiga
    bstFree(*rootPtr);

    // Constrói uma nova árvore balanceada a partir da lista de nós
    *rootPtr = buildBalancedTree(nodes, 0, size - 1);

    // Libera a memória do array de nós
    free(nodes);
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