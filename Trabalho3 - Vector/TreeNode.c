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

// Função auxiliar para coletar nós em ordem
void collectNodes(TNode *root, TNode **nodes, int *index) {
    if (root == NULL) {
        return;
    }
    collectNodes(root->left, nodes, index); // Guarda os nós da subárvore esquerda
    nodes[(*index)++] = root; // Adiciona o nó atual ao vetor
    collectNodes(root->right, nodes, index); // Guarda os nós da subárvore direita
}

// Função auxiliar para construir uma árvore balanceada a partir de um vetor
TNode *buildBalancedTree(TNode **nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2; // Encontra o meio do vetor
    TNode *node = nodes[mid]; // O nó do meio torna-se a raiz da subárvore
    node->left = buildBalancedTree(nodes, start, mid - 1); // Constrói a subárvore esquerda
    node->right = buildBalancedTree(nodes, mid + 1, end); // Constrói a subárvore direita
    return node;
}

// Função principal para balancear a árvore
void bstBalance(TNode **rootPtr) {
    if (*rootPtr == NULL) {
        return; // Se a árvore estiver vazia, não faz nada
    }
    // Guarda todos os nós em um vetor
    int size = 0;
    TNode *nodes[3000]; // Supondo que a árvore não terá mais de 3000 nós
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