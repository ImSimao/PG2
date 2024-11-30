#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define Max 256 // ler 255 characteres + '\0'

/*
     Função que compara duas strings de forma case-insensitive

     Parâmetros:
       str1: Ponteiro para a primeira string a ser comparada.
       str2: Ponteiro para a segunda string a ser comparada.

     Retorno:
       -1: Se str1 é lexicograficamente menor que str2.
        1: Se str1 é lexicograficamente maior que str2.
        0: Se as duas strings são iguais, ignorando diferenças de maiúsculas e minúsculas.
  */  
int strcmp_ic(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (tolower(*str1) < tolower(*str2))
            return -1;
        if (tolower(*str1) > tolower(*str2))
            return 1;
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 != '\0')
        return -1;
    if (*str1 != '\0' && *str2 == '\0')
        return 1;
    return 0;
}

int main()
{
    printf("indique as palavras: \n");
    char str1[Max];
    scanf("%s", str1);
    char str2[Max];
    scanf("%s", str2);
    int compare = strcmp_ic(str1, str2);
    if (compare == -1)
        printf("A string 1 é alfabeticamente superior a string 2");
    else if (compare == 1)
        printf("A string 1 é alfabeticamente inferior a string 2");
    else
        printf("As strings são alfabeticamente equivalentes");
}