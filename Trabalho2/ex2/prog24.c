#include <stdio.h>
#include "Sbooks.h"
#include "../ex1/processfile.h"

Collection c;

int main(int argc, char *argv[]){

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_ficheiro>\n", argv[0]);
        return 1;
    }

    
    
    int line = processFile(argv[1], collAddBook, &c);
    if (line < 0) {
            fprintf(stderr, "Erro ao processar o arquivo: %s\n", argv[1]);
            return 1;
        }

    for (int i = 0; i < c.count; i++) {
        printf("%s;%s;%s;%s;\n", c.books[i].title, c.books[i].isbn, c.books[i].authors, c.books[i].publisher);
    }

    return 0;
    
    

}