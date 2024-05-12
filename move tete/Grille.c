#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"

g * Grille_allouer(int n, int m)
{
    g* grille = malloc(sizeof(g));
    if( grille == NULL || n<=0 || m<=0 ) { return NULL; }

    grille->n = n;
    grille->m = m;

    grille->tab = malloc(n*sizeof(char**));
    int i, j;
    for (i=0; i<n; i++)
    {
        grille->tab[i] = malloc(m*sizeof(char*));
        for(j=0; j<m; j++)
        {
            grille->tab[i][j] = malloc(sizeof(char[8]));
        }
    }
    return grille;
}

void Grille_vider(g * grille)
{
    int i,j;
    for (i=0; i<grille->n; i++)
    {
        for(j=0; j<grille->m; j++)
        {
            grille->tab[i][j] = "  ";
        }
    }
}

int Sur_serpent(int x, int y)
{
    return 1;
}

void  Grille_tirage_fruit(g *grille)
{
    int x;
    int y;

    do{
        x=rand()%grille->n;
        y=rand()%grille->m;
    }while(Sur_serpent(x,y)==0);

    grille->fruit[0]=x;
    grille->fruit[1]=y;
}

void grille_desallouer(g *grille)
{
    int i;
    for(i=0;i<grille->n;i++){
        free(grille->tab[i]);
    }
    free(grille->tab);
}

void Grille_remplir(g* grille)
{

    grille->tab[grille->fruit[0]][grille->fruit[1]] = "1";
}

void Grille_serpent(g* grille, s* serp)
{
    //  mettre la ête du serpent sur la grille
    grille->tab[serp->tete[0]][serp->tete[1]] = "2";
    // on verifie qu'il y a des mouvements dans la liste
    if (serp->mov != NULL && serp->mov->lg >= 2) {
        lm* current_mvt = serp->mov->premier->suiv;
        clear();
        refresh();
        printw("dsvcdfdfvf");
        // parcours des mouvements à partir du deuxième
        while (current_mvt != NULL) {
            // mettre à jour la grille en fonction des mouvements
            for (int i = 1; i < serp->l->lg; i++) {
                if (current_mvt->direction == 'w')
                    grille->tab[serp->tete[0] - i][serp->tete[1]] = "2";
                else if (current_mvt->direction == 's')
                    grille->tab[serp->tete[0] + i][serp->tete[1]] = "2";
                else if (current_mvt->direction == 'd')
                    grille->tab[serp->tete[0]][serp->tete[1] - i] = "2";
                else if (current_mvt->direction == 'a')
                    grille->tab[serp->tete[0]][serp->tete[1] + i] = "2";
            }

            // mouvement suivant
            current_mvt = current_mvt->suiv;
        }
    }
}


void Grille_redessiner(g* grille)
{
    int i, j, x, y;

    // Calculate the starting coordinates to draw the grid in the center
    x = (getmaxx(stdscr) - grille->m * 2) / 2;
    y = (getmaxy(stdscr) - grille->n - 2) / 2;

    // Initialize color pairs
    start_color();
    init_color(COLOR_BLUE, 102, 178, 255);
    init_color(COLOR_GREEN, 0, 255, 0);
    init_color(COLOR_RED, 255, 0, 127);
    init_pair(1, COLOR_WHITE, COLOR_WHITE); // window background color
    init_pair(2, COLOR_WHITE, COLOR_RED); // color of the fruit
    init_pair(5, COLOR_WHITE, COLOR_GREEN); // color of the snake
    init_pair(3, COLOR_WHITE, COLOR_BLUE); // border color
    init_pair(4, COLOR_WHITE, COLOR_BLACK); //background of the grid color

    // loop through each cell of the grid and draw it
    for (i = 0; i < grille->n + 2; i++)
    {
        for (j = 0; j < grille->m + 2; j++)
        {
            //set the current position
            move(y + i, x + j * 2);

            // do the borders
            if (i == 0 || i == grille->n + 1 || j == 0 || j == grille->m + 1)
            {
                attron(COLOR_PAIR(3));
                printw("  ");
                attroff(COLOR_PAIR(3));
            }
            else
            {
                if (strcmp(grille->tab[i - 1][j - 1], "1") == 0) // fruit
                {
                    attron(COLOR_PAIR(2));
                    printw("  ");
                    attroff(COLOR_PAIR(2));
                }
                else if (strcmp(grille->tab[i - 1][j - 1], "2") == 0) // snake
                {
                    attron(COLOR_PAIR(5));
                    printw("  ");
                    attroff(COLOR_PAIR(5));
                }
                else // font of the grid
                {
                    attron(COLOR_PAIR(4));
                    printw("  ");
                    attroff(COLOR_PAIR(4));
                }
            }

            
        }
        printw("\n");
    }
    printw("\n");
}



//rassemble toutes les fonctions pour commencer avec la grille de depart
void draw_Grille(g* grille, s* serp, int fruit)
{
    Grille_vider(grille);
    if(fruit == 1)
    {
        Grille_tirage_fruit(grille);
    }
    Grille_remplir(grille);
    Grille_serpent(grille, serp);
    Grille_redessiner(grille);
}
