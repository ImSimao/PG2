#ifndef SLIB_H
#define SLIB_H


#define MAX_ISBN 16  //10-13


#define BLOCKSIZE 20

#define True 1
#define False 0

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