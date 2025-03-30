# Objetivo principal: compilar o executável
all: programa

# Compila funcoes.c em funcoes.o
funcoes.o: funcoes.c funcoes.h estruturas.h
	gcc -c funcoes.c

# Compila main.c em main.o
main.o: main.c funcoes.h estruturas.h
	gcc -c main.c

# Cria o executável 'programa' a partir de main.o e funcoes.o
programa: main.o funcoes.o
	gcc main.o funcoes.o -o programa

# Para executar o programa
run:
	./programa

# Para limpar os ficheiros-objeto e o executável
clean:
	rm -f *.o programa
