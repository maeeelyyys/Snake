#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

g* Grille_allouer(int n, int m)
{
    g* grille = malloc(sizeof(g));
    if( grille == NULL || n<=0 || m<=0 ) { return NULL; }

    grille->n = n;
    grille->m = m;

    grille->tab = malloc(n*sizeof(char**));
    int i;
    int j;
    for (i=0; i<n; i++)
    {
        grille->tab[i] = malloc(m*sizeof(char*))
        for(j=0; j<m, j++)
        {
            grill->tab[i][j] = malloc(sizeof(char[8]));
        }
    }
    return grille;
}

void Grille_vider(g* grille)
{
    int i,j;
    for (i=0; i<grill->n; i++)
    {
        for(j=0; j<grille->m; j++)
        {
            grille->tab[i][j] = "\33[00m  ";
            printf("%d\n", strlen(grille->tab[i][j] ));
        }  
    }
}

void  Grille_tirage_fruit(g *grille)
{
    int x;
    int y;

    do{
        x=rand()%grille->n;
        y=rand()%grille->m;
    }while(Sur_serpent(x,y)==true);

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
    //grille->tab[i] = "\33[00m  ";
}

bool Sur_serpent(int x, int y)
{
    return false;
}