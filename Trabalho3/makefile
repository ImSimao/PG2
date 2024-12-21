# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -g

# Alvos
TARGETS = main

# Ficheiros de objetos comuns
COMMON_OBJS = Older_Modules/processfile.o Older_Modules/filtros.o CollManage.o VecManage.o ListNode.o TreeNode.o

# Alvo padrão
default: all

# Apagar todos os binários e objetos
clean:
	rm -f $(TARGETS) *.o Older_Modules/*.o

# Regras gerais
all: $(TARGETS)

# Regra para compilar os programas
main: main.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $@ main.o $(COMMON_OBJS)

# Regras para compilar os ficheiros de objetos
main.o: main.c SLib.h
	$(CC) $(CFLAGS) -c main.c

Older_Modules/processfile.o: Older_Modules/processfile.c Older_Modules/processfile.h
	$(CC) $(CFLAGS) -c Older_Modules/processfile.c -o $@

Older_Modules/filtros.o: Older_Modules/filtros.c Older_Modules/filtros.h
	$(CC) $(CFLAGS) -c Older_Modules/filtros.c -o $@

# Regras para compilar ListNode e TreeNode
ListNode.o: ListNode.c ListNode.h
	$(CC) $(CFLAGS) -c ListNode.c -o $@

TreeNode.o: TreeNode.c TreeNode.h
	$(CC) $(CFLAGS) -c TreeNode.c -o $@

# Regras para compilar CollManage e VecManage
CollManage.o: CollManage.c CollManage.h
	$(CC) $(CFLAGS) -c CollManage.c -o $@

VecManage.o: VecManage.c VecManage.h
	$(CC) $(CFLAGS) -c VecManage.c -o $@