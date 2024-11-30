
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Sbooks.h"
#include "../ex1/processfile.h"

#define MAX_INPUT 128
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
    printf("Coleção carregada com %d livros.\n", c.count);

    collSortTitle(&c);

    char input[MAX_INPUT];
    while (1) {
        printf("\nLista de Comandos \nl - Listar coleção,\ni ISBN - Listar coleção por ISBN ou ISBN especifico,\na AUTOR - Lista livros do autor,\nq - Sair\n> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove o '\n' no final da entrada
        input[strcspn(input, "\n")] = '\0'; //strcspn retorna o tamanho da string ate o primeiro '\n'

        if (strcmp(input, "q") == 0) {
            break; // QUIT
        } else if (strcmp(input, "l") == 0) {
            
            for (int i = 0; i < c.count; i++) {
                printf("%s;%s;%s;%s;\n", c.books[i].title, c.books[i].isbn, c.books[i].authors, c.books[i].publisher);
            }
        }else if (strcmp(input, "i") == 0) {
            collSortRefIsbn(&c);
            for (int i = 0; i < c.count; i++) {
                printf("%s;%s;%s;%s;\n", c.refs[i]->title, c.refs[i]->isbn, c.refs[i]->authors, c.refs[i]->publisher);
            }
        }else if (strncmp(input, "i ", 2) == 0) {
            collSortRefIsbn(&c);
            const char *isbn = input + 2; // Recebe ISBN como argumento

            BookData key;
            strncpy(key.isbn, isbn, SIZE_ISBN - 1); // Preenche o campo isbn
                  
                    


            BookData **result = bsearch(&key, c.refs, c.count, sizeof(BookData *), cmpII);
            if (result) {
            
                printf("\n%s;%s;%s;%s;\n",
                       (*result)->title,
                       (*result)->isbn,
                       (*result)->authors,
                       (*result)->publisher);
            } else {
                printf("\nISBN %s não encontrado.\n", isbn);
            }
        }else if (strncmp(input, "a ", 2) == 0) {
            const char *name = input + 2;
            
            int found = 0;
            for (int i = 0; i < c.count; i++) {
                if (bookContainsAuthor(&c.books[i], name)) {
                    printf("%s;%s;%s;%s;\n",
                           c.books[i].title,
                           c.books[i].isbn,
                           c.books[i].authors,
                           c.books[i].publisher);
                    found++;
                }
            }
            printf("\nForam encontrados %d livros com o autor '%s'.\n", found, name);
        } else {
            printf("Comando inválido.\n");
        }
    
    }

    return 0;
        
}






