#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifndef _LISTE_SECTION_H
#define _LISTE_SECTION_H

typedef struct section {
  int  taille; /* valeur du maillon */
  int coord[2];
  struct section *suiv; /* adresse du maillon suivant */
}sec;

typedef struct liste_structure {
  struct section *premier; /* adresse du premier maillon de la liste, NULL si la liste est vide */
  struct section *dernier; /* adresse du dernier maillon de la liste NULL si la liste est vide */
  int lg; /* nombre de section dans la liste */
}ls;

/* allocation sur le tas pour un maillon de valeur v */
/* et renvoi de l'adresse du maillon */
sec* creer_section (unsigned t, int x, int y);

/* allocation sur le tas pour une liste vide */
/* et renvoi de l'adresse de la liste */
ls* creer_liste(int x, int y);

/* libération de l'espace mémoire occupé par la liste */
void desallouer_liste (ls **l);

/* libération de l'espace mémoire occupé par la section */
void desallouer_section (sec **s);

/* test de la vacuité de la liste d'adresse l */
int est_vide_liste(const ls *l);

/* affichage des valeurs de la liste d'adresse l */
void afficher_ls(const ls *l);

/* insertion du section d'adresse m au début de la liste d'adresse l */
void ajouter_sec_debut(ls *l, sec *s);

/* insertion d'un maillon d'adresse m à la fin de la liste d'adresse l */
void ajouter_sec_fin(ls *l, sec *s);

/* extraction du premier maillon de la liste d'adresse l */
/* et renvoi de l'adresse du maillon extrait */
sec *extraire_tete(ls *l);

/* extraction du dernier maillon de la liste d'adresse l */
/* et renvoi de l'adresse du maillon extrait */
sec *extraire_queue(ls *l);


#endif