#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processfile.h" 

/// Por Rever


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <nome_do_ficheiro> <string>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    char *filterValue = argv[2];

    int lines = processFile(filename, lineFilterPrint, filterValue);

    printf("Numero de Linhas Apresentadas: %d\n", lines);

    return 0;
}

