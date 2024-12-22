#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "filtros.h"


#define MAX_LINE_LENGTH 512

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

void separatorUnify(char str[])
{
    int i = 0, j = 0;

    // Ignora espaços ou tabs no início
    while (isspace(str[i])) {
        i++;
    }

    
    while (str[i] != '\0') {
        if (isspace(str[i])) {
            // Remove espaços desnecessários
            if (j > 0 && !isspace(str[j - 1])) {
                str[j] = ' ';  
                j++;
            }
        } else {
            // Copia caracteres 
            str[j] = str[i];
            j++;
        }
        i++;
    }

    // Remove espaço final, se existir
    if (j > 0 && isspace(str[j - 1])) {
        j--;
    }

    str[j] = '\0';
}

int strcmp_ic(const char *str1, const char *str2)
{
    while (*str1 != '\0')
    {
        if (tolower(*str1) < tolower(*str2))
            return -1;
        if (tolower(*str1) > tolower(*str2))
            return 1;
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0')
        return 0;
    return (*str1 == '\0') ? -1 : 1;
}