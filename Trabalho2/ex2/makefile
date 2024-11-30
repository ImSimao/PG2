# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -g

# Alvos
TARGETS = prog24 prog26 prog28 prog210

# Ficheiros de objetos comuns
COMMON_OBJS = ../ex1/processfile.o ../ex1/filtros.o

# Alvo padrão
default: all

# Apagar todos os binários e objetos
clean:
	rm -f $(TARGETS) *.o ../ex1/*.o

# Regras gerais
all: $(TARGETS)

# Regra para compilar os programas
prog24: prog24.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ prog24.o $(COMMON_OBJS)

prog26: prog26.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ prog26.o $(COMMON_OBJS)

prog28: prog28.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ prog28.o $(COMMON_OBJS)

prog210: prog210.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ prog210.o $(COMMON_OBJS)

# Regras para compilar os ficheiros de objetos
prog24.o: prog24.c sbooks.h
	$(CC) $(CFLAGS) -c prog24.c

prog26.o: prog26.c sbooks.h
	$(CC) $(CFLAGS) -c prog26.c

prog28.o: prog28.c sbooks.h
	$(CC) $(CFLAGS) -c prog28.c

prog210.o: prog210.c sbooks.h
	$(CC) $(CFLAGS) -c prog210.c

../ex1/processfile.o: ../ex1/processfile.c ../ex1/processfile.h
	$(CC) $(CFLAGS) -c ../ex1/processfile.c -o $@

../ex1/filtros.o: ../ex1/filtros.c ../ex1/filtros.h
	$(CC) $(CFLAGS) -c ../ex1/filtros.c -o $@
