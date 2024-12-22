
#ifndef VECMANAGE_H
#define VECMANAGE_H

#include "SLib.h"

VecBookRef *vecRefCreate(void);

int vecRefAdd(VecBookRef *vec, Book *book);

int vecRefSize( VecBookRef *vec );

Book *vecRefGet( VecBookRef *vec, int index );

int cmpTitle(const void *a, const void *b);

void vecRefSortTitle( VecBookRef *vec );

void vecRefSortIsbn( VecBookRef *vec );

Book *vecRefSearchIsbn( VecBookRef *vec, char *isbn );

void vecRefFree(VecBookRef *vec, int freeBooks);

#endif