#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

bool Sur_serpent(int x, int y){
    return false;
}

typedef struct grille {
    int n;
    int m;
    char*** tab;
    int fruit[2];
}g;

void  Grille_tirage_fruit(g *grille){
    int x;
    int y;

    do{
        x=rand()%grille->n;
        y=rand()%grille->m;
    }while(Sur_serpent(x,y)==true);

    grille->fruit[0]=x;
    grille->fruit[1]=y;
}

void grille_desallouer(g *grille){
    
    int i;
    for(i=0;i<grille->n;i++){
        free(grille->tab[i]);
    }
    free(grille->tab);
}




int main(){}