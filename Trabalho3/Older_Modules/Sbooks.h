#ifndef SBOOKS_H
#define SBOOKS_H

#define MAX_BOOKS 300 //296
#define MAX_TITLE 256 //200
#define SIZE_ISBN 16  //10-13
#define MAX_AUTHORS 128 // 92
#define MAX_PUB_NAME 64 // 51


typedef struct book { 
 char title[MAX_TITLE]; 
 char isbn[SIZE_ISBN]; 
 char authors[MAX_AUTHORS]; 
 char publisher[MAX_PUB_NAME]; 
} BookData; 
 
typedef struct{ 
 BookData books[MAX_BOOKS]; 
 BookData *refs[MAX_BOOKS]; 
 int count; // quantidade de elementos preenchidos em books 
} Collection;



#endif 