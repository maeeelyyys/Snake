#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifndef LISTE_SECTION_H_
#define LISTE_SECTION_H_


typedef struct maillon{
    struct maillon *suiv;
    int co[2];
}mai;

typedef struct section{
    int taille;
    struct section *suiv;
    struct maillon *debut;
    struct maillon *fin;
}sec;

typedef struct ListeSection{
    int lg;
    struct section *debut;
    struct section *fin;
}ls;


sec* creer_section(unsigned x, unsigned y);//ok

mai* creer_maillon(unsigned x, unsigned y);//ok

ls* creer_liste(unsigned x, unsigned y); //Ok

void desallouer_maillon(mai *m);//ok

void desallouer_section(sec *);//ok

void desallouer_liste(ls *l);//ok


mai* acceder_pos_liste(ls *l, unsigned pos); //normalement ok (fonction du cours)


void ajouter_section_queue(ls *l, mai *m);//mais pourquoi j'ai fais cette fonction

void ajouter_maillon_tete(ls *l,unsigned x, unsigned y,int t); //ok



void afficher_ls(ls *l);//ok


void supprimer_queue(ls *l);//en cours de traitement


#endif

