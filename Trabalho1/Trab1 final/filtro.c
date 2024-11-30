#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

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

//https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm
//https://www.tutorialspoint.com/c_standard_library/c_function_strtoul.htm
int main(int argc, char *argv[]) {

    if (argc != 3) {    //  Verifica o numero de argumentos passados
        fprintf(stderr, "Use: %s <número do campo> <string para comparar>\n", argv[0]);
        return 1;
    }

    unsigned long field_num = strtoul(argv[1], NULL, 10);
    if (field_num < 1) {    //verifica se o campo 1 é maior que 0
        fprintf(stderr, "O número do campo deve ser 1 ou superior.\n");
        return 1;
    }

    char *compStr = argv[2];
    separatorUnify(compStr);

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), stdin)) {
        char *p1 = line;
        char *p2;
        char ogLine[MAX_LINE_LENGTH];
        strcpy(ogLine, line);
        int current_field = 1;

        do {
            p2 = splitField(p1);
            if (current_field == field_num) {
                separatorUnify(p1);
                if (strcmp_ic(p1, compStr) == 0) {
                    printf("%s \n", ogLine); // print da linha original
                }
                break; 
            }
            current_field++;
            p1 = p2;
        } while (p1 != NULL);
    }

    return 0;


}
