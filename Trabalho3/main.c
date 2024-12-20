#include <stdio.h>
#include <string.h>

#include "Older_Modules/processfile.h"
#include "SLib.h"
#include "CollManage.h"
#include "VecManage.h"

#define MAX_INPUT 128

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_do_ficheiro>\n", argv[0]);
        return 1;
    }
    DynCollection *col = dynCollCreate();
    dynCollFill(col, argv[1]);

    char input[MAX_INPUT];
    while (1)
    {
        printf("\nLista de Comandos \nl - Listar coleção,\ni ISBN - Listar coleção por ISBN ou ISBN especifico,\na AUTOR - Lista livros do autor,\nq - Sair\n> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        // Remove o '\n' no final da entrada
        input[strcspn(input, "\n")] = '\0'; // strcspn retorna o tamanho da string ate o primeiro '\n'

        if (strcmp(input, "q") == 0)
        {
            //printf("Freeing collection...\n"); // Debugging 
            dynCollFree(col);
            //printf("Collection freed.\n"); // Debugging 
            break;                         // QUIT
        }
        else if (strcmp(input, "l") == 0)
        {
            for (int i = 0; i < vecRefSize(col->titleVec); i++)
            {
                Book *book = vecRefGet(col->titleVec, i);
                printf("Título: %s, ISBN: %s\n", book->title, book->isbn);
            }
        }
        else if (strcmp(input, "i") == 0)
        {
            // Additional functionality can be added here
        }
    }
}
