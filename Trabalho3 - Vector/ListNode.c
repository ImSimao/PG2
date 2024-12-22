#include "ListNode.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



// Função para adicionar um livro à lista
int lRefAdd(LNode **headPtr, Book *ref) {
    // Verifica se o livro já está na lista
    LNode *current = *headPtr;
    while (current != NULL) {
        if (strcmp(current->ref->title, ref->title) == 0) {
            return 0; // Livro já referenciado
        }
        current = current->next;
    }

    // Criação do novo nó
    LNode *newNode = malloc(sizeof(LNode));
    if (newNode == NULL) {
        return 0; // MemAlloc fail
    }
    newNode->ref = ref;
    newNode->next = NULL;

    // Inserção na lista ordenada
    if (*headPtr == NULL || strcmp((*headPtr)->ref->title, ref->title) > 0) {
        // Inserir no início
        newNode->next = *headPtr;
        *headPtr = newNode;
    } else {
        // Encontrar a posição correta para inserção
        LNode *prev = NULL;
        current = *headPtr;
        while (current != NULL && strcmp(current->ref->title, ref->title) < 0) {
            prev = current;
            current = current->next;
        }
        // Inserir o novo nó
        newNode->next = current;
        prev->next = newNode;
    }

    return 1; // Sucesso
}

void lRefPrint(LNode *head) {
    LNode *current = head; // Inicia no cabeçalho da lista

    // Verifica se a lista está vazia
    if (current == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    // Percorre a lista e imprime os dados dos livros
    while (current != NULL) {
        // Imprime os dados do livro
        printf("Título: %s; ISBN: %s; Autor(es): %s ; Editora: %s ;\n",
                current->ref->title, current->ref->isbn, current->ref->authors, current->ref->publisher);

        current = current->next; // Avança para o próximo nó
    }
}

void lRefFree(LNode *head) {
    LNode *current = head; // Inicia no cabeçalho da lista
    LNode *nextNode;       // Ponteiro para o próximo nó

    // Percorre a lista e liberta a memória dos nós
    while (current != NULL) {
        nextNode = current->next; // Armazena o próximo nó
        free(current);             // Liberta o nó atual
        current = nextNode;        // Avança para o próximo nó
    }
}