#include <stdio.h>
#include <stdlib.h>


#include "VecManage.h"
#include "CollManage.h"
#include "SLib.h"
#include "Older_Modules/processfile.h"







DynCollection *dynCollCreate(void) {
    DynCollection *col = malloc(sizeof(*col));
    if (col == NULL) {
        return NULL;
    }


    col->titleVec = vecRefCreate();
    if (col->titleVec == NULL) {
        free(col);
        return NULL;
    }


    col->isbnVec = vecRefCreate();
    if (col->isbnVec == NULL) {
        vecRefFree(col->titleVec, 0); // Não libera os livros pois ainda não existem
        free(col);
        return NULL;
    }


    return col;
}



int dynCollAddBook(const char *line, void *context) {
    if (line == NULL || context == NULL) return 0;

    DynCollection *col = (DynCollection *)context;
    Book *b = bookCreate(line);
    if (b == NULL) return 0;

    // Primeiro tenta adicionar ao vetor de títulos
    if (vecRefAdd(col->titleVec, b) != 0) {
        bookFree(b);
        return 0;
    }

    // Se falhar ao adicionar ao vetor ISBN, desfaz a adição ao vetor de títulos
    if (vecRefAdd(col->isbnVec, b) != 0) {
        // Remove do vetor de títulos (última posição)
        col->titleVec->size--;
        bookFree(b);
        return 0;
    }

    return 1;
}

void dynCollFill(DynCollection *coll, const char *filename) {
    if (coll == NULL || filename == NULL) return; // Verifica se a coleção e o arquivo são válidos

    // Preenche a coleção usando processFile e dynCollAddBook
    processFile(filename, dynCollAddBook, coll);

    // Ordena os vetores de referências pelos critérios especificados
    vecRefSortTitle(coll->titleVec);
    vecRefSortIsbn(coll->isbnVec);
    return;
}


void dynCollFree(DynCollection *coll) {
    if (coll == NULL) {
        printf("Warning: Attempted to free a NULL collection.\n");
        return; // Prevents dereferencing a NULL pointer
    }
    
    //printf("Freeing ISBN vector...\n");
    vecRefFree(coll->isbnVec, True); 
    //printf("Freeing Title vector...\n");
    vecRefFree(coll->titleVec, False);
    //printf("Freeing collection...\n");
    free(coll);
}