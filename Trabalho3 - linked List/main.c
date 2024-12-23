#include <stdio.h>
#include <string.h>

#include "Older_Modules/processfile.h"

#include "SLib.h"
#include "CollManage.h"
#include "VecManage.h"

#include "TreeNode.h" 
#include "ListNode.h" 

#define MAX_INPUT 128



TNode *authorTree = NULL; // BST innit

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <nome_do_ficheiro>\n", argv[0]);
        return 1;
    }
    const char *fileName = argv[1];

    DynCollection *col = dynCollCreate();
    if(col == NULL){
		printf("Erro na criação de coll\n");
		return -1;
	}
    dynCollFill(col, fileName);

    // Innit the binary search tree for authors
    for (int i = 1; i < vecRefSize(col->titleVec); i++){
        Book *book = vecRefGet(col->titleVec, i);    

        char authors[strlen(book->authors)]; // Copia o conteúdo de book->authors para authors 
        strcpy(authors, book->authors); // Usado para não alterar o conteúdo de book->authors

        char *token = strtok(authors, " "); // Divide autores por espaço
        while (token != NULL){
            bstAdd(&authorTree, token, book); // Adiciona cada palavra à BST
            token = strtok(NULL, " "); // Obtém a próxima palavra
        }
    }
    bstBalance(&authorTree);  
    //printBST(authorTree, 0);

    char input[MAX_INPUT];
    while (True)
    {
        printf("\nLista de Comandos \nl - Listar coleção,\ni - Listar ordenado por ISBN\ni ISBN - Pesquisar por um ISBN especifico,\na AUTOR - Lista livros do autor,\nq - Sair\n> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        // Remove o '\n' no final da entrada
        input[strcspn(input, "\n")] = '\0'; // strcspn retorna o tamanho da string ate o primeiro '\n'

        if (strcmp(input, "q") == 0)    // QUIT
        {
            //printf("Freeing collection...\n"); // Debugging 
            dynCollFree(col);
            //printf("Collection freed.\n"); // Debugging 
            bstFree(authorTree); // Free the BST
            //printf("BST freed.\n");
            break;                         
        }
        else if (strcmp(input, "l") == 0)   // LIST books ordered by title
        {
            for (int i = 1; i < vecRefSize(col->titleVec); i++)
            {
                Book *book = vecRefGet(col->titleVec, i);
                printf("Título: %s; ISBN: %s; Autor(es): %s ; Editora: %s ;\n",
                book->title, book->isbn, book->authors, book->publisher);
            }
        }
        else if (strcmp(input, "i") == 0)   // LIST books ordered by ISBN
        {
            for (int i = 1; i < vecRefSize(col->isbnVec); i++)
            {
                Book *book = vecRefGet(col->isbnVec, i);
                printf("Título: %s; ISBN: %s; Autor(es): %s ; Editora: %s ;\n",
                book->title, book->isbn, book->authors, book->publisher);
            }
        }else if (strncmp(input, "i ", 2) == 0) // Search for a specific ISBN
        {
            char isbn[MAX_INPUT];
            sscanf(input + 2, "%s", isbn); // Lê o ISBN após o comando "i "
            

            Book *foundBook = vecRefSearchIsbn(col->isbnVec, isbn); // Pesquisa pelo ISBN
            if (foundBook != NULL)
            {
                printf("Título: %s; ISBN: %s; Autor(es): %s ; Editora: %s ;\n",
                foundBook->title, foundBook->isbn, foundBook->authors, foundBook->publisher);
            }
            else
            {
                printf("Livro com ISBN %s não encontrado\n", isbn);
            }
        }
        else if (strncmp(input, "a ", 2) == 0) // Search for books written by author
        {
            char author[MAX_INPUT];
            sscanf(input + 2, "%s", author); // Read the author's name after the command "a "

            LNode *foundBooks = bstSearch(authorTree, author); // Search for the author in the BST
            if (foundBooks != NULL)
            {
                lRefPrint(foundBooks); // Print the list of books for the author
            }
            else
            {
                printf("Nenhum livro encontrado para o autor %s\n", author);
            }
        }
    }
}
