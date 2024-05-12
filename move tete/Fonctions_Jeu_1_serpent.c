#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"
#include "Grille.h"

void getMenu()
{
    char* title = "JEU SNAKE";
    char* message = "ENTREZ SPACE TO START";
    char* message1 = "ENTREZ Q POUR QUITTER";
    int max_y = getmaxy(stdscr)/2;
    int max_x = getmaxx(stdscr)/2 - strlen(title)/2;
    move(max_y, max_x);
    attron(A_BOLD);
    printw(title);
    attroff(A_BOLD);
    move(max_y + 9, getmaxx(stdscr)/2 - strlen(message)/2);
    printw(message);
    move(max_y + 12, getmaxx(stdscr)/2 - strlen(message1)/2);
    printw(message1);
        
}

void move_serpent(g* grille)
{
    int ch=0;
    s * serpent = malloc(sizeof(s));
    serpent->tete[0] = (grille->m)-1;
    serpent->tete[1] = 0;
    serpent->fruits =0;
    serpent->l = creer_liste();
    serpent->mov = creer_liste_mouvement();
    char direction = 'd';
    draw_Grille(grille, serpent, 1);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    wbkgd(stdscr, COLOR_PAIR(1));
    while (ch!='q')
    {
        ch = getch();
        if (ch != ERR) {
            switch (ch)
            {
                case 'w':
                case 'z':
                case KEY_UP:
                    
                        direction = 'w';
                    break;
                case 'a':
                case 'q':
                case KEY_LEFT:
                        direction = 'a';
                    break;
                case 's':
                case KEY_DOWN:
                        direction = 's';
                    break;
                case 'd':
                case KEY_RIGHT:
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
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
                case 'a':
                    if (serpent->tete[1] > 0)
                        serpent->tete[1] -= 1;
                    else {
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
                case 's':
                    if (serpent->tete[0] < (grille->n) - 1)
                        serpent->tete[0] += 1;
                    else {
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
                case 'd':
                    if (serpent->tete[1] < grille->m - 1)
                        serpent->tete[1] += 1;
                    else {
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
            }
        }

        ajouter_mvt_fin(serpent->mov, creer_mouvement(serpent->tete[0], serpent->tete[1], direction));

        if (atefruit(grille, serpent) == 1) {
            serpent->fruits+=1;
            ajouter_sec_fin(serpent->l, creer_section(1));

        }
        
        clear();
        refresh();
        draw_Grille(grille, serpent, atefruit(grille, serpent));
        
    }
        
    free(serpent);
}

void endscreen_loose(s* serpent)
{
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1));

    clear();
    refresh();
    printw("fdsfdf");
    printw("%d", serpent->l->lg);
}

int atefruit(g* grille, s * serp){
  if (grille->fruit[0] == serp->tete[0] && grille->fruit[1] == serp->tete[1]){
      return 1;     
  }
  return 0;
}