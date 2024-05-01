#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


typedef struct maillon{
    struct maillon *suiv;
    int co[2];
}mai;

typedef struct section{
    int taille;
    char *couleur;
    struct section *suiv;
    struct maillon *debut;
    struct maillon *fin;
}sec;

typedef struct ListeSection{
    int long;
    struct section *debut;
    struct section *fin;
}ls;


sec* creer_section();
mai* creer_maillon();
void supprimer_maillon_fin;
void desallouer_section();
ls* creer_liste(){}
void ajouter_section_tete();
void ajouter_section_queue();
void ajouter_maillon_tete();

void desallouer_liste();



