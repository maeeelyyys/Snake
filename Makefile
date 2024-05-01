all: Grille.o main.o
	gcc -Wall Grille.o main.o -o programme
     
Grille.o:  Grille.c Grille.h
	gcc -c -Wall -std=c99 -Wfatal-errors Grille.c

main.o: main.c Grille.h
	gcc -c -Wall -std=c99 -Wfatal-errors main.c 
