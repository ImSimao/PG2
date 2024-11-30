#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define Max 256 // ler 255 characteres + '\0'

// https://www.ibm.com/docs/en/i/7.4?topic=functions-strchr-search-character#strchr__title__8

/*
    Esta função procura a primeira ocorrência de ';' na string fornecida e divide-a nesse ponto.
    Se ';' for encontrado, substitui por '\0' e retorna o ponteiro para o caractere após ';'.
    Se ';' não for encontrado, retorna NULL.
*/
char *splitField(char *str)
{
    char *p = strchr(str, ';');
    if (p != NULL)
    {
        *p = '\0';
        return p + 1;
    }
    return NULL;
}


int main()
{

    
        char s[] = "primeiro;; terceiro \t;  ; palavras   do quinto \n";
        char *p1 = s, *p2;
        do
        {
            p2 = splitField(p1);
            printf("{%s}", p1);
        } while ((p1 = p2) != NULL);
    
}