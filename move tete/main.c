#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"
#include "Liste_section.c"

int main(int argc, char** argv)
{   
    ls *l=creer_liste();
    printf("----------------------\n");

    afficher_ls(l);

    sec *s=creer_section(2);
    ajouter_sec_fin(l,s);
    printf("----------------------\n");
    afficher_ls(l);


    printf("----------------------\n");
    sec *p=creer_section(3);
    ajouter_sec_debut(l,p);
    afficher_ls(l);
    printf("----------------------\n");

    sec *u=extraire_queue(l);

    afficher_ls(l);
    printf("----------------------\n");

    desallouer_section(&u);
    desallouer_liste(&l);


    /*
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
        init_pair(2, COLOR_WHITE, COLOR_BLUE); //foreground , background color
        wbkgd(stdscr, COLOR_PAIR(2));
        wrefresh(stdscr);
        init_pair(1, COLOR_BLACK, COLOR_MAGENTA); //foreground , background color
        attron(COLOR_PAIR(1)); //applique la paire de couleurs avec l'index 1 à la fenêtre courante
    }

    //dimensions de la grille
    int n = atoi(argv[1]); //lignes
    int m = atoi(argv[2]); //colonnes

    // Temps d'exécution max de getch à .../10eme de seconde
    halfdelay(atoi(argv[3]));

    clear();
    int start = 0;

    do{
        ch = getch();
        if(start == 0)
        {
            getMenu();
        }
        switch(ch)
        {
            case 'e':
                clear();
                refresh();
                move(0,0);
                //afficher la grille
                g * grille = Grille_allouer(n, m);
                move_serpent(grille);
                start = 1;
                break;
                ;;
        }

    }while(ch !=' ');


    //fin de ncurses 
    endwin();
    return 0;
    */
}
