#include <stdio.h>
#include "processfile.h"



int main(int argc, char *argv[]) {
    // Verifica se o nome do arquivo foi passado como argumento
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1; // Retorna erro
    }

    const char *filename = argv[1];
    int lineCount = processFile(filename, linePrintRaw, NULL);
    
    if (lineCount < 0) {
        return 1; // Retorna erro se processFile falhar
    }

    printf("\nTotal de linhas lidas: %d\n", lineCount);
    return 0;
}