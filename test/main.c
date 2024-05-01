#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Grille.h"

int main(int argc, char** argv)
{
    /* Initialisation de ncurses et du clavier(4 lignes)*/
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    // si le nombre d'arguments n'est pas suffisant quitter le prog
	if(argc !=5)
		return 1;
    srand(time(NULL));

    //dimensions de la grille
    int n = atoi(argv[1]); //lignes
    int m = atoi(argv[2]); //colonnes

    // Temps d'exécution max de getch à .../10eme de seconde
    halfdelay(argv[3]);  

    g * grille_test = Grille_allouer(n, m);
    Grille_vider(grille_test);
    Grille_tirage_fruit(grille_test);
    Grille_remplir(grille_test);
    Grille_redessiner(grille_test);

    endwin();
}
