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
    serpent->tete[0] = (grille->m)-1;
    serpent->tete[1] = 0;
    //serpent->l = creer_liste(serpent->tete[0],serpent->tete[1]);
    //ajouter_maillon_tete(serpent->l,serpent->tete[0],serpent->tete[1]);

    char direction = 'd';
    draw_Grille(grille, serpent, 1);
    while (ch!=' ')
    {
        ch = getch();
        if (ch != ERR) {
            switch (ch)
            {
                case 'w':
                    if (direction != 's')
                        direction = 'w';
                    break;
                case 'a':
                    if (direction != 'd')
                        direction = 'a';
                    break;
                case 's':
                    if (direction != 'w')
                        direction = 's';
                    break;
                case 'd':
                    if (direction != 'a')
                        direction = 'd';
                    break;
            }
        }
        else {
            switch (direction)
            {
                case 'w':
                    if (serpent->tete[0] > 0)
                        serpent->tete[0] -= 1;
                    else {
                        endscreen_loose();
                        return;
                    }
                    break;
                case 'a':
                    if (serpent->tete[1] > 0)
                        serpent->tete[1] -= 1;
                    else {
                        endscreen_loose();
                        return;
                    }
                    break;
                case 's':
                    if (serpent->tete[0] < (grille->n) - 1)
                        serpent->tete[0] += 1;
                    else {
                        endscreen_loose();
                        return;
                    }
                    break;
                case 'd':
                    if (serpent->tete[1] < grille->m - 1)
                        serpent->tete[1] += 1;
                    else {
                        endscreen_loose();
                        return;
                    }
                    break;
            }
        }
        
        if (atefruit(grille, serpent) == 1) {
            endscreen_loose();
            refresh();
        }
        
        clear();
        refresh();
        draw_Grille(grille, serpent, 0);
    }
        
    free(serpent);
}

void endscreen_loose()
{
    clear();
    refresh();
    printw("fdsfdf");
}

int atefruit(g* grille, s * serp){
  if (grille->fruit[0] == serp->tete[0] && grille->fruit[1] == serp->tete[1]){
    Grille_tirage_fruit(grille);
    return 1;     
  }
  return 0;
}