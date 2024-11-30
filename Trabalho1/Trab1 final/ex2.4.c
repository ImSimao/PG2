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

/*
    Esta função remove os separadores de uma string.

    - remove espaços em branco do início da string;
    - substitui tabs por espaços;
    - remove '\n' e outros espaços em branco do meio da string;
    - remove espaços em branco do fim da string.
*/
void separatorUnify(char str[])
{
    while (isspace(str[0]))
    {
        for (int i = 0; i < strlen(str); i++)
        {
            str[i] = str[i + 1];
        }
    }

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '\t')
        {
            str[i] = ' ';
        }
        if (str[i] == '\n')
        {
            str[i] = str[i + 1];
        }
        if (isspace(str[i]) && ((isspace(str[i + 1])) || (str[i + 1] == '\0')))
        {
            for (int j = i; j < strlen(str); j++)
            {
                str[j] = str[j + 1];
            }
            i--;
        }
    }
}

int main()
{
    char input[Max];
    while (fgets(input, Max, stdin))
    {
        char *p1 = input, *p2;
        do
        {
            p2 = splitField(p1);
            separatorUnify(p1);
            printf("{%s}", p1);
        } while ((p1 = p2) != NULL);

        printf("\n"); // cria uma linha de intervalo para facilidade de leitura
    }
}