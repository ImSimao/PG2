#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "processfile.h"
#include "filtros.h"
#include "Sbooks.h"


#include "../SLib.h"
#include "../VecManage.h"
#include "../CollManage.h"

#define MAX_LINE_LENGTH 512

// https://www.geeksforgeeks.org/basics-file-handling-c/

int processFile(const char *filename,
                int (*action)(const char *line, void *context),
                void *context)
{
    FILE *file;
    char line[512]; // Buffer para armazenar cada linha
    int total = 0;  // Variável para acumular o numero de resultados

    // Abre o arquivo para leitura
    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo"); // Imprime mensagem de erro
        return -1;                         // Retorna -1 em caso de erro
    }

    // Lêr o ficheiro linha a linha
    while (fgets(line, sizeof(line), file) != NULL)
    {
        total += action(line, context); // Chama a função action e acumula o resultado
    }

    // Fecha o arquivo
    fclose(file);

    return total;
}

int linePrintRaw(const char *line, void *context)
{

    printf("%s", line); // Print da linha no terminal

    return 1;
}

int lineFilterPrint(const char *line, void *context)
{
    // Verifica se linha ou contexto são nulos
    if (line == NULL || context == NULL)
    {
        return 0;
    }

    // Cria cópias para manipulação
    char lineCopy[MAX_LINE_LENGTH];
    strcpy(lineCopy, line);

    char *p1 = lineCopy;

    // Separa o primeiro campo
    splitField(p1);

    // Uniformiza o primeiro campo
    separatorUnify(p1);

    // Compara o primeiro campo com o contexto
    if (strcmp_ic(p1, (const char *)context) == 0)
    {
        linePrintRaw(line, NULL); // Imprime a linha original
        return 1;                 // Indica que a linha foi impressa
    }

    return 0; // Indica que a linha não foi impressa
}

int collAddBook(const char *line, void *context)
{
    // Verifica se a linha ou o contexto são nulos
    if (line == NULL || context == NULL)
    {
        return 0; // erro
    }

    Collection *collection = (Collection *)context;

    // Verifica se a coleção atingiu a capacidade máxima
    if (collection->count >= MAX_BOOKS)
    {
        return 0; // erro
    }

    BookData *b = &collection->books[collection->count];

    if (fillBookData(b, line) == 0)
    {
        return 0; // erro
    }

    collection->count++; // fillBookData com sucesso, incrementa o count da coleção

    return 1; // Sucesso
}

int fillBookData(BookData *b, const char *line)
{
    char *p1 = (char *)line;
    char *p2;
    int current_field = 1;
    int field_count = 0;

    do
    {
        p2 = splitField(p1);
        separatorUnify(p1);
        if (current_field == 1)
        {
            strcpy(b->title, p1);
        }
        else if (current_field == 2)
        {
            strcpy(b->isbn, p1);
        }
        else if (current_field == 4)
        {
            strcpy(b->authors, p1);
        }
        else if (current_field == 5)
        {
            strcpy(b->publisher, p1);
        }
        current_field++;
        p1 = p2;
        field_count++;
    } while (p1 != NULL && field_count < 5);

    return 1;
}

int cmpT(const void *a, const void *b)
{
    BookData *a1 = (BookData *)a;
    BookData *b1 = (BookData *)b;
    return strcmp_ic(a1->title, b1->title);
}

int cmpI(const void *a, const void *b)
{
    const BookData *bookA = *(const BookData **)a; // Desreferencia o ponteiro
    const BookData *bookB = *(const BookData **)b; // Desreferencia o ponteiro

    // Comparar pelo ISBN
    return strcmp(bookA->isbn, bookB->isbn);
}
int cmpII(const void *key, const void *elem)    // Destinado a ser usado em bsearch
{
    const BookData *book = *(const BookData **)elem; // Desreferencia o BookData pointer
    const BookData *isbnKey = (const BookData *)key; // Desreferencia o ponteiro

    return strcmp(isbnKey->isbn, book->isbn); // Compara os ISBNs
}

void collSortTitle(Collection *col)
{
    qsort(col->books, col->count, sizeof *col->books, cmpT);
}

void collSortRefIsbn(Collection *col)
{
    // Inicializa o array de ponteiros refs
    for (int i = 0; i < col->count; i++)
    {
        col->refs[i] = &col->books[i]; // Cada ponteiro em refs aponta para o respectivo livro em books
    }

    // Ordena o array de ponteiros usando qsort
    qsort(col->refs, col->count, sizeof(BookData *), cmpI);
}



void toLowerCase(const char *src, char *dest) {
    while (*src) {
        *dest++ = tolower(*src++);
    }
    *dest = '\0';
}


// https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
// https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm

int bookContainsAuthor(BookData *b, const char *word)
{
    if (word == NULL || strlen(b->authors) == 0) return 0;

    char authorsCopy[MAX_AUTHORS];
    strcpy(authorsCopy, b->authors);

    // Caso de busca com mais de uma palavra (nome completo)
    if (strchr(word, ' ') != NULL) {
        char lowerStr1[MAX_AUTHORS], lowerStr2[MAX_AUTHORS];
       
        separatorUnify(authorsCopy);

        toLowerCase(authorsCopy, lowerStr1);    //usa uma func toLowerCase porque é const word
        toLowerCase(word, lowerStr2);

        //strstr -> procura a primeira ocorrência de word(agulha) na string authorsCopy (palheiro)
        return strstr(lowerStr1, lowerStr2) != NULL;       
    }


    // Caso de busca por um único nome
    char *token = strtok(authorsCopy, " ,");
    while (token != NULL) {
        separatorUnify(token);
        if (strcmp_ic(token, word) == 0) return 1;
        token = strtok(NULL, " ,");
    }

    return 0;
}



////////////    SE 3        ////////////////////////

Book *bookCreate(const char *line) {
    if (line == NULL) {
        return NULL; // Invalid line
    }

    Book *b = malloc(sizeof(Book));
    if (b == NULL) {
        return NULL; // MemAlloc fail
    }

    // Inicializar todos os campos
    b->title = NULL;
    b->authors = NULL;
    b->publisher = NULL;
    b->isbn[0] = '\0'; // Inicializa o ISBN como uma string vazia

    char *lineCopy = strdup(line); // Duplicar linha
    if (lineCopy == NULL) {
        bookFree(b);
        return NULL; // Falha na alocação de memória
    }

    char *token = strtok(lineCopy, ";");
    if (token != NULL) {
        b->title = (char *)malloc(strlen(token) + 1);
        if (b->title == NULL) {
            free(lineCopy);
            bookFree(b);
            return NULL; // Falha na alocação de memória
        }
        strcpy(b->title, token); // Copiar o título
    }

    token = strtok(NULL, ";");
    if (token != NULL) {
        // Presumindo que b->isbn é um array de caracteres já alocado
        strncpy(b->isbn, token, MAX_ISBN - 1);
        b->isbn[MAX_ISBN - 1] = '\0'; // Garantir que a string esteja terminada
    }

    token = strtok(NULL, ";");  // Pular ISBN-13
    token = strtok(NULL, ";");
    if (token != NULL) {
        b->authors = (char *)malloc(strlen(token) + 1);
        if (b->authors == NULL) {
            free(lineCopy);
            bookFree(b);
            return NULL; // Falha na alocação de memória
        }
        strcpy(b->authors, token); // Copiar os autores
    }

    token = strtok(NULL, ";");
    if (token != NULL) {
        b->publisher = (char *)malloc(strlen(token) + 1);
        if (b->publisher == NULL) {
            free(lineCopy);
            bookFree(b);
            return NULL; // Falha na alocação de memória
        }
        strcpy(b->publisher, token); // Copiar o nome do editor
    }

    free(lineCopy); // Liberar a linha duplicada
    return b; // Retornar o livro
}
    
void bookFree(Book *b) {
    if (b != NULL) {
        free(b->title);
        free(b->authors);
        free(b->publisher);
        free(b);
    }
}


int cmpISBN(const void *a, const void *b) {
    // Desreferencia os ponteiros para obter os livros
    const Book *bookA = *(const Book **)a; // Desreferencia a primeira referência
    const Book *bookB = *(const Book **)b; // Desreferencia a segunda referência

    // Compara os ISBNs dos livros
    return strcmp(bookA->isbn, bookB->isbn);
}



