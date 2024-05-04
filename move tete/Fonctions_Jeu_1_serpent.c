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
    draw_Grille(grille, serpent);
    while (ch!=' ')
    {
        ch = getch();
        
        switch (ch)
        {
        case 'w':
            serpent->tete[0] -= 1;
            break;
        case 'a':
            serpent->tete[1] -= 1;
            break;
        case 's':
            serpent->tete[0] += 1;
            break;
        case 'd':
            serpent->tete[1] += 1;
            break;
        }
        clear();
        refresh();
        draw_Grille(grille, serpent);

    }
    //free(serpent);
}
