#include "Grille.h"


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
            grille->tab[i][j] = "\33[00m  ";
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
    grille->tab[grille->fruit[0]][grille->fruit[1]] = "\33[41m  ";
}

void Grille_redessiner(g* grille)
{
    int i,j;

    for (i=0; i<grille->n+2; i++)
    {
        for(j=0; j<grille->m+2; j++)
        {
            if(i == 0 || i == (grille->n+1) || j == 0 || j == (grille->m+1) )
            {
                        printf("\33[42m  ");
            }
            else
            {
           	        printf("%s", grille->tab[i-1][j-1]);
            }
        }
        printf("\33[00m  ");
        printf("\n");
    }
    printf("\n");
}


