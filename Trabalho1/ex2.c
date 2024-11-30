#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define Max 256 // ler 255 characteres + '\0'

// https://www.ibm.com/docs/en/i/7.4?topic=functions-strchr-search-character#strchr__title__8
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

/* ###OLD###SplitField###Working###
char *splitField(char *str)
{
    while (*str != ';' && *str != '\0')
    {
        str++;
    }

    if (*str == ';')
    {
        *str = '\0';
        return str + 1;
    }
    return NULL;
}



*/

void separatorUnify(char str[])
{
    while(isspace(str[0]))
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
        if (str[i] == '\n') // Duvida
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

    
/*  2.3
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
*/
}