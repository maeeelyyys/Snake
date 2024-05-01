#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef GRILLE_H_
#define GRILLE_H_


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

void Grille_desallouer(g* grille);

void Grille_redessiner(g* grille);

void Grille_remplir_serpent(g * grille);






#endif // Grille
