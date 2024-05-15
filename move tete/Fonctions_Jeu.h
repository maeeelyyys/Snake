//Ce fichier .h va contenir les entêtes des fonctions de gestion des jeux à coder
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "Grille.h"

void getMenu(); // affiche la fenetre de base "menu"
void choose_mode(int n, int m);
void endscreen_win(s* serpent);
void endscreen_loose(); // affiche la fenetre de fin de jeu quand on perd
void show_title();
void endscreen_loose(s* serpent); // affiche la fenetre de fin de jeu quand on perd
void move_serpent(g* grille, unsigned mode_chosen); // boucle du jeu a 1 serpent 
int atefruit(g* grille, s* serp); // renvoie un bool suivant si le fruit a ete mange par le serpent
void move_serpent(g* grille, unsigned mode_chosen); // boucle du jeu a 1 serpent
int move_serpent_right(g* grille, s* serpent, unsigned mode_chosen);
int move_serpent_down(g* grille, s* serpent, unsigned mode_chosen);
int move_serpent_left(g* grille, s* serpent, unsigned mode_chosen);
int move_serpent_up(g* grille, s* serpent, unsigned mode_chosen);
int move_serpent_direction(g* grille, s* serpent, char direction, unsigned mode_chosen);
void bouger_corps(s* serpent, g * grille);
int is_collision(g* grille, int x, int y, unsigned mode_chosen);

char mov_one_player(int ch, char direction);
char mov_two_player(int ch, char direction2);