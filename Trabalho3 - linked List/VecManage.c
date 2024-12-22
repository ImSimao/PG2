#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SLib.h"
#include "Older_Modules/processfile.h"
#include "VecManage.h"
#include "Older_Modules/filtros.h"




VecBookRef *vecRefCreate ( void ){
	
    VecBookRef *vec = malloc(sizeof *vec);
    if(vec == NULL)return NULL; // MemAlloc fail
    
    vec->size = 0;			//	inicializar size a zero
    vec->space = BLOCKSIZE;//	inicializar space com BlockSize = 20 espaços
    
    vec->refs = malloc(vec->space * sizeof(*vec->refs));
    if(vec->refs == NULL){	// MemAlloc fail
		free(vec);
		return NULL;
    }
    return vec;
}



int vecRefAdd(VecBookRef *vec, Book *ref) {
    if (vec == NULL || ref == NULL) return -1; // Invalid input

    if (vec->refs == NULL) {
        vec->refs = malloc(BLOCKSIZE * sizeof(*vec->refs));
        if (vec->refs == NULL) return -1; // Verificar falha de alocação
    }
    
    // Resize if necessary
    if (vec->size >= vec->space) {
        vec->space += BLOCKSIZE; // Add 20 more spaces
        Book **temp = realloc(vec->refs, vec->space * sizeof(*vec->refs));
        if (temp == NULL) {
            return -1; // MemAlloc fail
        }
        vec->refs = temp; // Atualizar o ponteiro para o novo espaço
    }
    vec->refs[vec->size++] = ref; // Add the book(ref)
    return 0; // Success
}



int vecRefSize( VecBookRef *vec ){
    if (vec != NULL) return vec->size;
    else return 0;
}



Book *vecRefGet( VecBookRef *vec, int index ){
    if (vec== NULL || index >= vec->size || index < 0) return NULL; // check if args are valid
    return vec->refs[index];
}


int cmpTitle(const void *a, const void *b)
{
    const Book *a1 = *(const Book **)a; // Desreferencia o ponteiro
    const Book *b1 = *(const Book **)b; // Desreferencia o ponteiro
    return strcmp_ic(a1->title, b1->title);
}

void vecRefSortTitle( VecBookRef *vec ){
    if (vec != NULL && vec->refs != NULL && vec->size > 0){
        qsort(vec->refs, vec->size, sizeof(Book *), cmpTitle);
    }
    
}


void vecRefSortIsbn( VecBookRef *vec ){
    if (vec != NULL && vec->refs != NULL && vec->size > 0){
        qsort(vec->refs, vec->size, sizeof(Book *), cmpISBN);
    }
}

/*
Book *vecRefSearchIsbn( VecBookRef *vec, char *isbn ){

    if(vec == NULL || isbn == NULL) return NULL;
    vecRefSortIsbn(vec);
    return bsearch(isbn, vec->refs, vec->size, sizeof(Book *), cmpISBNForSearch);
}
*/
Book *vecRefSearchIsbn(VecBookRef *vec, char *isbn) {
    Book *key = malloc(sizeof(Book)); // Criar book temporário
    if (key == NULL) return NULL; // MemAlloc fail

    strcpy(key->isbn, isbn); // Copiar ISBN para key
    printf("Buscando livro com ISBN: %s\n", key->isbn);

    Book **res = bsearch(&key, vec->refs, vec->size, sizeof *vec->refs, cmpISBN);

    free(key); // Liberar a memória do book temporário

    // Retornar NULL caso não encontre o ISBN ou retornar o book que contém o ISBN
    if (res == NULL) {
        return NULL; // Não encontrou o ISBN
    } else {
        return *res; // Retornar o book que contém o ISBN
    }
}



void vecRefFree(VecBookRef *vec, int freeBooks) {
    if (vec == NULL) {
        printf("Warning: Attempted to free a NULL vector.\n");
        return; 
    }
    
    //printf("Freeing vector with size: %d\n", vec->size);

    if (freeBooks) {
        for (int i = 0; i < vec->size; i++) {
            bookFree(vec->refs[i]); // Libertar cada descritor de livro
        }
    }
    //printf("Freeing references...\n");
    free(vec->refs); // Libertar o array de referências
    //printf("Freeing vector...\n");
    free(vec); // Libertar o vetor em si
}