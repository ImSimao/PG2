#ifndef SLIB_H
#define SLIB_H

#define MAX_BOOKS 300 //296
#define MAX_TITLE 256 //200
#define MAX_ISBN 16  //10-13
#define MAX_AUTHORS 128 // 92
#define MAX_PUB_NAME 64 // 51


typedef struct {  // Descritor dos dados de um livro 
 char *title;  //  string alojada dinamicamente 
 char isbn[MAX_ISBN]; // string com dimensão fixa 
 char *authors;   //  string alojada dinamicamente 
 char *publisher; //  string alojada dinamicamente 
} Book;




typedef struct{  // Descritor de um vetor 
 Book **refs; //  array alojado dinamicamente 
 int size;   //  quantidade de elementos preenchidos 
 int space;  //  quantidade de elementos alojados 
} VecBookRef;


typedef struct{  // Descritor de um vetor 
 VecBookRef *titleVec; //  vetor a ordenar por título 
 VecBookRef *isbnVec;  //  vetor a ordenar por isbn 
} DynCollection;



#endif 