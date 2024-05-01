#include "Liste_section.h"



mai* creer_maillon(int x, int y){
    mai *m;
    m->co[0]=x;
    m->co[1]=y;
    m->suiv=NULL;
    return m;
}

sec* creer_section(int x, int y){
    mai *m=creer_maillon(x,y);

    sec *s;
    s->taille=1;
    s->debut=m;
    s->suiv=NULL;
    s->couleur=malloc(sizeof(char)*8);
    s->couleur="\33[00m";
    s->fin=m;
    return s;
}

ls* creer_liste(int x, int y){
    sec *s=creer_section(x,y);

    ls *l;
    l->lg=1;
    l->debut=s;
    l->fin=s;

    return l;
}






void desallouer_liste();

void supprimer_maillon_fin();
void desallouer_section();
void ajouter_section_tete();


mai* acceder_pos_liste(ls *l, unsigned pos){
    mai *m = l->debut->debut;
    while (m != NULL && pos > 0) {
        m = m->suiv;
        pos--;
    }
    return m;
}

void ajouter_section_queue(ls *l, mai *m){
    mai *tmp;
    tmp=acceder_pos_liste(l,l->lg-1);

    tmp->suiv=m;
    ++l->lg;

    sec *s;
    s=l->debut;
    while(s->suiv!=NULL){

        s = s->suiv;
    }
    ++s->taille;
    s->fin=m;
}




void ajouter_maillon_tete(ls *l,sec *s, mai *m){
    /*Si le serpent tourne*/
    if (s->debut==NULL){
            s->fin=m;
    }
    m->suiv=s->debut;
    s->debut=m;

    ++l->lg;
    ++s->taille;
}


void supprimer_maillon_fin(ls *l){
    if(l->debut==NULL){
        return;
    }
    sec *s;
    s=l->debut;
    while(s->suiv!=NULL){
        s = s->suiv;
    }
    mai *m=s->debut;

    if(m->suiv==NULL){
        desallouer_section(l);
    }else{
    while (m->suiv->suiv!=NULL){
        m=m->suiv;
    }
    m->suiv=NULL;
    }
}

void desallouer_section(ls *l){
    sec *s=l->debut;

    s->debut;
    s->fin=NULL;

}


