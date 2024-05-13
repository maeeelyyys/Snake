#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"
#include "Liste_section.c"

int main(int argc, char** argv)
{   
    fprintf(stdout, "\x1B[5mRELANCEZ LE JEU ! \x1B[0m\n");
    
    // Initialisation de ncurses et du clavier(4 lignes)
	initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    int ch;

    // si le nombre d'arguments n'est pas suffisant quitter le prog
	if(argc !=5)
		return 1;
    srand(time(NULL));

    //Initialisation des couleurs
    if (has_colors()) 
    { 
        start_color();
        init_pair(2, COLOR_WHITE, COLOR_WHITE); //foreground , background color
        wbkgd(stdscr, COLOR_PAIR(2));
        wrefresh(stdscr);
        init_pair(1, COLOR_BLACK, COLOR_WHITE); //foreground , background color
        attron(COLOR_PAIR(1)); //applique la paire de couleurs avec l'index 1 à la fenêtre courante
    }

    //dimensions de la grille
    int n = atoi(argv[1]); //lignes
    int m = atoi(argv[2]); //colonnes

    // Temps d'exécution max de getch à .../10eme de seconde
    halfdelay(atoi(argv[3]));

    clear();
    do{
        ch = getch();
        getMenu();
        switch(ch)
        {
            case ' ':
                clear();
                refresh();
                move(0,0);
                choose_mode(n, m);
                break;
                ;;
        }

    }while(ch !='q');


    //fin de ncurses 
    endwin();
    return 0;
  
}
