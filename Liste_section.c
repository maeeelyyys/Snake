#include "Liste_section.h"



sec* creer_section();



mai* creer_maillon();
void supprimer_maillon_fin();
void desallouer_section();
ls* creer_liste();
void ajouter_section_tete();


mai* acceder_pos_liste(ls *l, unsigned pos){
    mai *m;
    for(m=l->debut;m!=NULL; && pos!=0;pos--){
        m = m->suiv;
    }
    return m;
}

void ajouter_section_queue(ls *l, mai *m){
    mai *tmp;
    tmp=acceder_pos_liste(l,l-1);

    tmp.suiv=m;
    ++l->long;

    sec *s;
    s=l->debut;
    while(s.suiv!=NULL){

        s = s->suiv;
    }
    ++s->taille;
    s->fin=m;
}




void ajouter_maillon_tete(ls *l,sec *s, mai *m){
    /*Si le serpent tourne*/
    if (sec->debut=NULL){
            sec->fin=m;
    }
    m->suiv=sec->debut;
    sec->debut=m;

    ++ls->long;
    ++sec->taille;
}



void supprimer_maillon_fin(ls *l){
    if(ls->debut=NULL){
        return;
    }
    sec *s;
    s=l->debut;
    while(s.suiv!=NULL){
        s = s->suiv;
    }
    mai *m=s->debut;

    if(m->suiv==NULL){
        desallouer_section();
    }else{
    while (m->suiv->suiv!=NULL){
        m=m->suiv;
    }
    m->suiv==NULL;
    }
}

void desallouer_section(ls *l){
    sec *s=ls->debut;

    s->debut;
    s->fin=NULL;

    free()
}


void desallouer_liste();
