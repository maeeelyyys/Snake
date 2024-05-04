all: Grille.o main.o Fonctions_Jeu_1_serpent.o Serpent.o
	gcc -Wall Grille.o Fonctions_Jeu_1_serpent.o Serpent.o main.o -o programme -lncurses
     
Grille.o:  Grille.c Grille.h Serpent.h
	gcc -c -Wall -std=c99 -Wfatal-errors Grille.c

Serpent.o:  Serpent.c Serpent.h
	gcc -c -Wall -std=c99 -Wfatal-errors Serpent.c

Fonctions_Jeu_1_serpent.o:  Fonctions_Jeu_1_serpent.c Fonctions_Jeu.h
	gcc -c -Wall -std=c99 -Wfatal-errors Fonctions_Jeu_1_serpent.c

main.o: main.c Grille.h Fonctions_Jeu.h Serpent.h
	gcc -c -Wall -std=c99 -Wfatal-errors main.c 

clean:
	rm -f *.o programme