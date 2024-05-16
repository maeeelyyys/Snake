#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
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
            grille->tab[i][j] = malloc(sizeof(char[10]));
            grille->tab[i][j]->elem = malloc(sizeof(char*));

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
            grille->tab[i][j]->elem = "  ";
        }
    }
}

int Case_vide(g* grille,int x, int y)
{
    if(strcmp(grille->tab[x][y]->elem,"body")==0 ||strcmp(grille->tab[x][y]->elem,"tete")==0 || strcmp(grille->tab[x][y]->elem,"mob")==0 || strcmp(grille->tab[x][y]->elem,"fruit")==0){
        return 1;
    }
    return 0;
}

void Grille_tirage_fruit(g *grille, unsigned mode_chosen)
{
    int x;
    int y;

    do{
        x=rand()%grille->n;
        y=rand()%grille->m;
    }while(Case_vide(grille,x,y));

    grille->fruit[0]=x;
    grille->fruit[1]=y;

    if(mode_chosen == '2' || mode_chosen == '3')
    {
       // generer une couleur de fruit differente a chaque fois que un fruit a ete mange et doit donc etre re affiche
        int tmp = grille->couleur_fruit;
        do{
            grille->couleur_fruit = rand()%5 +4;
        }while(grille->couleur_fruit == tmp);
    }
    else
    {
        grille->couleur_fruit = 5;
    }
    
}
void Grille_tirage_monstre(g *grille,int nb)
{
    int x;
    int y;
    int i;

    for(i=0;i<nb;i++){
        do{
            x=rand()%grille->n;
            y=rand()%grille->m;
        }while(Case_vide(grille,x,y));

        grille->mob[i + grille->mobs][0]=x;
        grille->mob[i + grille->mobs][1]=y;

    }
    grille->mobs += nb;

    
}
void grille_desallouer(g *grille)
{
    int i,j;
    for(i=0;i<grille->n;i++){
        for(j=0;j<grille->m;j++){
            free(grille->tab[i][j]->elem);
            free(grille->tab[i][j]);
        }
        free(grille->tab[i]);
    }
    free(grille->tab);
}

void Grille_remplir(g* grille)
{
    grille->tab[grille->fruit[0]][grille->fruit[1]]->elem = "fruit";
    
    int i;

    //Le mode Pve implique 5 monstres en permanence
    for(i=0;i<grille->mobs;i++){
        grille->tab[grille->mob[i][0]][grille->mob[i][1]]->elem="mob";
    }
    
}

void Grille_serpent(g* grille, s* serp)
{
    //  mettre la tête du serpent sur la grille
    grille->tab[serp->tete[0]][serp->tete[1]]->elem = "tete";
    grille->tab[serp->l->premier->coord[1]][serp->l->premier->coord[0]]->elem = "tete";
    sec * tmp = serp->l->premier;
    while (tmp != NULL){
        if(tmp == serp->l->premier->suiv)
            grille->tab[tmp->coord[1]][tmp->coord[0]]->elem = "tete";
        else
            grille->tab[tmp->coord[1]][tmp->coord[0]]->elem = "body";
        tmp = tmp->suiv;
    }
    
}


void Grille_redessiner(g* grille)
{
    int i, j, x, y;
    //coordinates to draw the grid in the center
    x = (getmaxx(stdscr) - grille->m * 2) / 2;
    y = (getmaxy(stdscr) - grille->n - 2) / 2;

    // Initialize color pairs
    start_color();
    init_color(COLOR_BLUE, 102, 178, 255);
    init_pair(1, COLOR_BLACK, COLOR_WHITE); // window background color
    init_pair(3, COLOR_WHITE, COLOR_BLUE); // border color
    init_pair(2, COLOR_WHITE, COLOR_BLACK); //background of the grid color

    init_color(COLOR_GREEN, 0, 255, 0); //apple
    init_color(COLOR_RED, 255, 0, 127); //strawberry
    init_color(COLOR_MAGENTA, 255, 153, 51); //orange
    init_color(COLOR_YELLOW, 255, 255, 51); //lime
    init_color(COLOR_CYAN, 255, 153, 255); //peach
    init_pair(4, COLOR_WHITE, COLOR_GREEN); // color of the snake (BASE)
    init_pair(5, COLOR_WHITE, COLOR_RED); // color of the fruit
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA); // color of the fruit
    init_pair(7, COLOR_WHITE, COLOR_YELLOW); // color of the fruit
    init_pair(8, COLOR_WHITE, COLOR_CYAN); // color of the fruit
    init_pair(9, COLOR_WHITE, COLOR_MAGENTA); // color of the worm


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
                if (strcmp(grille->tab[i - 1][j - 1]->elem, "fruit") == 0) // fruit
                {
                    attron(COLOR_PAIR(grille->couleur_fruit));
                    printw("  ");
                    attroff(COLOR_PAIR(grille->couleur_fruit));
                }
                else if (strcmp(grille->tab[i - 1][j - 1]->elem, "body") == 0) // snake
                {
                    attron(COLOR_PAIR(grille->couleur_snake));
                    printw("  ");
                    attroff(COLOR_PAIR(grille->couleur_snake));
                }
                else if (strcmp(grille->tab[i - 1][j - 1]->elem, "tete") == 0) // snake
                {
                    attron(COLOR_PAIR(grille->couleur_snake));
                    printw("<3");
                    attroff(COLOR_PAIR(grille->couleur_snake));
                }
                else if (strcmp(grille->tab[i - 1][j - 1]->elem, "mob") == 0) // Mode pve
                {
                    attron(COLOR_PAIR(1));
                    printw("  ");
                    attroff(COLOR_PAIR(1));
                }
                else // font of the grid
                {
                    attron(COLOR_PAIR(2));
                    printw("  ");
                    attroff(COLOR_PAIR(2));
                }
            }


            
        }
        printw("\n");
    }
    printw("\n");
}



//rassemble toutes les fonctions pour commencer avec la grille de depart
void draw_Grille(g* grille, s* serp, int fruit, unsigned mode_chosen, s* serp1)
{
    Grille_vider(grille);
    Grille_serpent(grille, serp);
    if(fruit == 1)
    {
        Grille_tirage_fruit(grille, mode_chosen);
        if(mode_chosen=='1' && grille->n>9 && grille->m>9)
        {
            Grille_tirage_monstre(grille,5);
        }
    }
    Grille_remplir(grille);
    Grille_serpent(grille, serp);
    if (mode_chosen == '3' && serp1 != NULL)
        Grille_serpent(grille, serp1);
    Grille_redessiner(grille);
}
