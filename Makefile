CC = gcc
CFLAGS = -ansi -pedantic -Wall -W -Werror -g
all: main

# Règle 1
main: main.o 
	$(CC) -o main.o 
	make clean

# Efface tous les fichiers temporaires
clean:
	rm -f *.bak rm -f *.o
