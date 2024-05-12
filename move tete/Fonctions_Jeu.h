//Ce fichier .h va contenir les entêtes des fonctions de gestion des jeux à coder
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "Grille.h"

void getMenu(); // affiche la fenetre de base "menu"
void move_serpent(g* grille); // boucle du jeu a 1 serpent 
void endscreen_loose(); // affiche la fenetre de fin de jeu quand on perd
int atefruit(g* grille, s* serp); // renvoie un bool suivant si le fruit a ete mange par le serpent