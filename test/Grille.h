#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Serpent.h"
//struct de la grille contenant le nombre de lignes (n), colonnes (m), un tableau
//de tableau pour faire la grille dont chaque element contient une liste de charactere,
//les coordonnees du fruit
typedef struct {

    int n;
    int m;
    char*** tab;
    int fruit[2];
} g;

// prenant en entrée un deux entiers n et m qui retourne un pointeur sur une Grille,
//dont le tableau est également alloué, c’est à dire que chacune de ses cases contient une chaîne de caractères de taille 8
g * Grille_allouer(int n, int m);

void Grille_vider(g* grille);

void Grille_tirage_fruit(g* grille);

void Grille_remplir(g* grille);

void Grille_serpent(g* grille, s* serp);

void Grille_desallouer(g* grille);

void Grille_redessiner(g* grille);

void draw_Grille(g* grille, s* serp);

void Grille_remplir_serpent(g * grille);