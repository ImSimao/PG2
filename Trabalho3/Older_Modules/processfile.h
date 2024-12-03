
#ifndef PROCESSFILE_H
#define PROCESSFILE_H

#include "Sbooks.h"
#include "../SLib.h"

int processFile(const char *filename,
                int (*action)(const char *line, void *context),
                void *context);

// Para exercicio 1
int linePrintRaw(const char *line, void *context);

int lineFilterPrint(const char *line, void *context);

// Para exercicio 2

int collAddBook(const char *line, void *context);

int fillBookData(BookData *b, const char *line);

int cmpT(const void *a, const void *b);

int cmpI(const void *a, const void *b);

int cmpII(const void *key, const void *elem);

void collSortTitle(Collection *col);

void collSortRefIsbn(Collection *col);

void toLowerCase(const char *src, char *dest);

int bookContainsAuthor(BookData *b, const char *word);

//  SE 3

Book *bookCreate(const char *line);

void bookFree(Book *b);



#endif
