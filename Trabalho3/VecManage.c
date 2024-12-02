#include <stdlib.h>


#include "SLib.h"
#include "processfile.h"





VecBookRef *vecRefCreate(void) {
    VecBookRef *vr = (VecBookRef *)malloc(sizeof(VecBookRef));
    if (vr == NULL) {
        return NULL; // MemAlloc fail
    }
    vr->size = 0;
    vr->space = 10; // Valor Inicial
    vr->refs = (Book **)malloc(vr->space * sizeof(Book *));
    if (vr->refs == NULL) {
        free(vr);
        return NULL; // MemAlloc fail
    }
    return vr;
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



void vecRefSize( VecBookRef *vr ){
    if (vr != NULL) return vr->size;
    else return 0;

}


Book *vecRefGet( VecBookRef *vr, int index ){
    if (vr== NULL || index == vr->size) return NULL;
    return vr->refs[index];
}



int cmpTitle(const void *a, const void *b)
{
    Book *a1 = (Book **)a;
    Book *b1 = (Book **)b;
    return strcmp_ic(a1->title, b1->title);
}

void vecRefSortTitle( VecBookRef *vr ){
    if (vr != NULL){
        qsort(vr->refs, vr->size, sizeof(Book *), cmpTitle);
    }
    
}


void vecRefSortIsbn( VecBookRef *vr ){

    if (vr != NULL)
    {
        qsort(vr->refs, vr->size, sizeof(Book *), cmpI);
    }
    
}


Book *vecRefSearchIsbn( VecBookRef *vr, char *isbn ){

}


void vecRefFree( VecBookRef *vr, int freeBooks ){

}