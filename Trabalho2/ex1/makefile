# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -g

# Alvos
TARGETS = prog13 prog15

# Ficheiros de objetos comuns
COMMON_OBJS = processfile.o filtros.o

# Alvo padrão
default: all

# Apagar tudo
clean:
	rm -f $(TARGETS) *.o

# Regras gerais
all: $(TARGETS)

# Compilar prog13
prog13: prog13.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ prog13.o $(COMMON_OBJS)

# Compilar prog15
prog15: prog15.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ prog15.o $(COMMON_OBJS)

# Regras para compilar os ficheiros de objetos
prog13.o: prog13.c processfile.h filtros.h
	$(CC) $(CFLAGS) -c prog13.c

prog15.o: prog15.c processfile.h filtros.h
	$(CC) $(CFLAGS) -c prog15.c

processfile.o: processfile.c processfile.h
	$(CC) $(CFLAGS) -c processfile.c

filtros.o: filtros.c filtros.h
	$(CC) $(CFLAGS) -c filtros.c
