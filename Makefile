all: Grille.o main.o
	gcc -Wall Grille.o main.o -o programme

Liste_section.o : Liste_section.h Liste_section.c
	gcc -c -Wall -std=c99 -Wfatal-errors Liste_section.c
     
Grille.o:  Grille.c Grille.h
	gcc -c -Wall -std=c99 -Wfatal-errors Grille.c

main.o: main.c Grille.h
	gcc -c -Wall -std=c99 -Wfatal-errors main.c 
