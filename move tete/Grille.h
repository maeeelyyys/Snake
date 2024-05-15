
#include "Serpent.h"

#define  TRUE 1
#define  FALSE 0

#ifndef GRILLE_H_
#define GRILLE_H_

typedef struct Case{
    char* elem;
}c;

typedef struct Grille_jeu{

    int n;
    int m;
    c*** tab;
    int fruit[2];
    int mob[5][2];
    int couleur_fruit; //pour la couleur du nouveau fruit
    int couleur_snake; // pour la couleur du fruit mange
} g;




// prenant en entrée un deux entiers n et m qui retourne un pointeur sur une Grille,
//dont le tableau est également alloué, c’est à dire que chacune de ses cases contient une chaîne de caractères de taille 8
g * Grille_allouer(int n, int m);

void Grille_vider(g* grille);

int Case_vide(g* grille,int x,int y);

void Grille_tirage_fruit(g* grille, unsigned mode_chosen);

void Grille_tirage_monstre(g* grille, int nb);

void Grille_remplir(g* grille);

void Grille_serpent(g* grille, s* serp);

void Grille_desallouer(g* grille);

void Grille_redessiner(g* grille);

void draw_Grille(g* grille, s* , int fruit, unsigned mode_chosen);

void Grille_remplir_serpent(g * grille);

#endif // GRILLE_H_
