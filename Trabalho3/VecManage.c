#include <stdlib.h>


#include "SLib.h"
#include "processfile.h"
#include "VecManage.h"





VecBookRef *vecRefCreate(void) {
    VecBookRef *vec = (VecBookRef *)malloc(sizeof(VecBookRef));
    if (vec == NULL) {
        return NULL; // MemAlloc fail
    }
    vec->size = 0;
    vec->space = 10; // Valor Inicial
    vec->refs = (Book **)malloc(vec->space * sizeof(Book *));
    if (vec->refs == NULL) {
        free(vec);
        return NULL; // MemAlloc fail
    }
    return vec;
}



int vecRefAdd(VecBookRef *vec, Book *book) {
    if (vec == NULL || book == NULL) return -1; // Invalid input
    
    // Resize if necessary
    if (vec->size >= vec->space) {
        vec->space += 10; // Add 10 more spaces
        vec->refs = (Book **)realloc(vec->refs, vec->space * sizeof(Book *));
        if (vec->refs == NULL) {
            return -1; // MemAlloc fail
        }
    }
    vec->refs[vec->size] = book; // Add book 
    vec->size++;
    return 0; // Success
}



void vecRefSize( VecBookRef *vec ){
    if (vec != NULL) return vec->size;
    else return 0;
}



Book *vecRefGet( VecBookRef *vec, int index ){
    if (vec== NULL || index == vec->size) return NULL;
    return vec->refs[index];
}



int cmpTitle(const void *a, const void *b)
{
    Book *a1 = (Book **)a;
    Book *b1 = (Book **)b;
    return strcmp_ic(a1->title, b1->title);
}

void vecRefSortTitle( VecBookRef *vec ){
    if (vec != NULL){
        qsort(vec->refs, vec->size, sizeof(Book *), cmpTitle);
    }
    
}


void vecRefSortIsbn( VecBookRef *vec ){

    if (vec != NULL)
    {
        qsort(vec->refs, vec->size, sizeof(Book *), cmpI);
    }
    
}


Book *vecRefSearchIsbn( VecBookRef *vec, char *isbn ){

    if(vec == NULL || *isbn == NULL) return NULL;
    vecRefSortIsbn(vec);
    return bsearch(isbn, vec->refs, vec->size, sizeof(Book *), cmpII);
}


void vecRefFree(VecBookRef *vec, int freeBooks) {
    if (vec == NULL) return; 

    if (freeBooks) {
        for (int i = 0; i < vec->size; i++) {
            free(vec->refs[i]); // Libertar cada descritor de livro
        }
    }

    free(vec->refs); // Libertar o array de referências
    free(vec); // Libertar o vetor em si
}