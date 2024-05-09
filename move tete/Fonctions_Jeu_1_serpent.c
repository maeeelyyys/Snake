#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"
#include "Fonction_l.c"

void getMenu()
{
    char* message = "JEU SNAKE";
    int max_y = getmaxy(stdscr)/2;
    int max_x = getmaxx(stdscr)/2 - strlen(message)/2;
    move(max_y, max_x);
    printw("%s", message);
}

void move_serpent(g* grille)
{
    int ch=0;
    s * serpent = malloc(sizeof(s));
    serpent->tete[0] = 0;
    serpent->tete[1] = (grille->n)-1;
    //serpent->l = creer_liste(serpent->tete[0],serpent->tete[1]);
    //ajouter_maillon_tete(serpent->l,serpent->tete[0],serpent->tete[1]);
    draw_Grille(grille, serpent, 1);
    while (ch!=' ')
    {
        ch = getch();
        
        switch (ch)
        {
        case 'w':
            if(serpent->tete[0] <= 0)
            {
                endscreen_loose();
                return;
            }
            //if(grille->tab[serpent->tete[0]][serpent->tete[1]])
            else serpent->tete[0] -= 1;

            break;
        case 'a':
            if(serpent->tete[1] <= 0)
            {
               endscreen_loose();
               return;
            }
            else serpent->tete[1] -= 1;
            break;
        case 's':
            if(serpent->tete[0] >= (grille->n)-1)
            {
               endscreen_loose();
               return;
            }
            else serpent->tete[0] += 1;
            break;
        case 'd':
            if(serpent->tete[1] >= grille->m-1)
            {
               endscreen_loose();
               return;
            }
            else serpent->tete[1] += 1;
            break;
        }
        clear();
        refresh();
        draw_Grille(grille, serpent,0);

    }
    free(serpent);
}

void endscreen_loose()
{
    clear();
    refresh();
    printw("fdsfdf");
}
