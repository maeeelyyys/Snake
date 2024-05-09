all: Grille.o main.o Fonctions_Jeu_1_serpent.o Serpent.o
	gcc -Wall Grille.o Fonctions_Jeu_1_serpent.o Serpent.o main.o -o programme -lncurses

Fonction_l.o:  Fonction_l.c Fonction_l.h
	gcc -c -Wall -std=c99 -Wfatal-errors Liste_section.c

Serpent.o:  Serpent.c Serpent.h Liste_section.h
	gcc -c -Wall -std=c99 -Wfatal-errors Serpent.c

Grille.o:  Grille.c Grille.h Serpent.h
	gcc -c -Wall -std=c99 -Wfatal-errors Grille.c

Fonctions_Jeu_1_serpent.o:  Fonctions_Jeu_1_serpent.c Fonctions_Jeu.h Grille.h Liste_section.h
	gcc -c -Wall -std=c99 -Wfatal-errors Fonctions_Jeu_1_serpent.c

main.o: main.c Fonctions_Jeu.h 
	gcc -c -Wall -std=c99 -Wfatal-errors main.c 

clean:
	rm -f *.o programme