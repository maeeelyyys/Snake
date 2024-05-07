#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"

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
    serpent->tete[0] = (grille->n)-1;
    serpent->tete[1] = 0;
    draw_Grille(grille, serpent, 1);
    while (ch!=' ')
    {
        ch = getch();
        
        switch (ch)
        {
        case 'w':
            serpent->tete[0] -= 1;
            if(serpent->tete[0]==-1)
            {
                endscreen_loose();
            }
            break;
        case 'a':
            serpent->tete[1] -= 1;
            if(serpent->tete[1]==-1)
            {
                endscreen_loose();
            }
            break;
        case 's':
            serpent->tete[0] += 1;
            if(serpent->tete[0]== grille->n)
            {
                endscreen_loose();
            }
            break;
        case 'd':
            serpent->tete[1] += 1;
            if(serpent->tete[1]==grille->)
            {
                endscreen_loose();
            }
            break;
        }
        clear();
        refresh();
        //free la grille
        draw_Grille(grille, serpent,0);

    }
    free(serpent);
}

void endscreen_loose()
{
    clear();
    refresh();
    printw("fdsfdf");
    e
}
