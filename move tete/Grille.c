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
    // Placer la tête du serpent sur la grille
    grille->tab[serp->tete[0]][serp->tete[1]] = "2";

    // Parcourir la liste de sections du serpent
    sec* current_sec = serp->l->premier;
    lm* current_mvt = serp->mov->premier;
    
    while (current_sec != NULL && current_mvt != NULL) {
        // Mettre à jour la grille en fonction de chaque section et mouvement
        for (int i = 1; i <= current_sec->taille; i++) {
            if (current_mvt->direction == HAUT) {
                grille->tab[serp->tete[0] - i][serp->tete[1]] = "2";
            } else if (current_mvt->direction == BAS) {
                grille->tab[serp->tete[0] + i][serp->tete[1]] = "2";
            } else if (current_mvt->direction == GAUCHE) {
                grille->tab[serp->tete[0]][serp->tete[1] - i] = "2";
            } else if (current_mvt->direction == DROITE) {
                grille->tab[serp->tete[0]][serp->tete[1] + i] = "2";
            }
        }

        // Passer à la section et au mouvement suivant dans les listes
        current_sec = current_sec->suiv;
        current_mvt = current_mvt->suiv;
    }
}

void Grille_redessiner(g* grille)
{
    int i,j,x,y;
    x = getmaxx(stdscr)/2 - (grille->m);
    y = getmaxy(stdscr)/2 - (grille->n)/2;
    //move(y,x);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); //foreground , background color
    wbkgd(stdscr, COLOR_PAIR(2));
    wrefresh(stdscr);
    init_color(COLOR_RED, 240, 105, 119);
    init_color(COLOR_GREEN, 178, 240, 159);
    init_color(COLOR_BLUE, 159, 189, 240);
    init_pair(2,COLOR_WHITE, COLOR_RED);
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    init_pair(4,COLOR_WHITE,COLOR_BLACK);
    init_pair(5,COLOR_WHITE,COLOR_GREEN);

    for (i=0; i<grille->n+2; i++)
    {
        for(j=0; j<grille->m+2; j++)
        {
            attron(COLOR_PAIR(1));

            if(i == 0 || i == (grille->n+1) || j == 0 || j == (grille->m+1) )
            {
                if(i==0 || j==0) getyx(stdscr,y,x);
                attron(COLOR_PAIR(3));
                printw("  ");
                attroff(COLOR_PAIR(3));
            }
            else
            {
                if(strcmp(grille->tab[i-1][j-1],"1") ==0)
                {
                    attron(COLOR_PAIR(2));
                    printw("  ");
                    attroff(COLOR_PAIR(2));
                }
                else if(strcmp(grille->tab[i-1][j-1],"2") ==0)
                {
                    attron(COLOR_PAIR(5));
                    printw("  ");
                    attroff(COLOR_PAIR(5));
                }
           	    else
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
