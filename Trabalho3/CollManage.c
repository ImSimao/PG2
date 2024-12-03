#include <stdio.h>


#include "VecManage.h"
#include "CollManage.h"
#include "SLib.h"
#include "Older_Modules/processfile.h"

#define True 1
#define False 0





DynCollection *dynCollCreate(void) {
    DynCollection *col = (DynCollection *)malloc(sizeof(DynCollection));
    if (col == NULL) {
        return NULL; // MemAlloc fail
    }

    col->titleVec = vecRefCreate(); // Inicializa titleVec
    col->isbnVec = vecRefCreate(); // Inicializa isbnVec

    if (col->titleVec == NULL || col->isbnVec == NULL) {
        free(col);
        return NULL; // MemAlloc fail
    }

    return col;
}



int dynCollAddBook( const char *line, void *context ){  //Rever // Erro de logica possivelmente em Context = vr

    if (line == NULL || context == NULL) return 0;

    Book *b = bookCreate(*line);
    VecBookRef *vr = vecRefCreate();
    vr = vecRefAdd(vr, b);

    if( b == NULL || vr == NULL) return 0;

    context = vr;

    return 1;
    
    
}

void dynCollFill( DynCollection *coll, FILE *f ){

    processFile(f, dynCollAddBook, coll);

    vecRefSortTitle(coll->titleVec);
    vecRefSortIsbn(coll->isbnVec);
    return;
}


void dynCollFree( DynCollection *coll ){

    vecRefFree(coll->isbnVec, True);        //ver em que lib, True se encontra
    vecRefFree(coll->titleVec, True);
    free(coll);
    return;
}