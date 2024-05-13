#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Serpent.h"

#define  TRUE 1
#define  FALSE 0

#ifndef GRILLE_H_
#define GRILLE_H_

typedef struct Case{
    char* couleur;
    int timer;
}c;

typedef struct Grille_jeu{

    int n;
    int m;
    c*** tab;
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

void draw_Grille(g* grille, s* , int fruit);

void Grille_remplir_serpent(g * grille);

#endif // GRILLE_H_
