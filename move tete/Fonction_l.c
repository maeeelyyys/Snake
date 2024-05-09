
mai* creer_maillon(unsigned x, unsigned y){
    /*Description fonction*/

    /*Initialisation du struct maillon*/
    mai *m= malloc(sizeof(mai));

    if (m == NULL) {
        /* Gestion des erreurs d'allocation de m�moire */
        printf("Erreur : Impossible d'allouer de la memoire pour le maillon.\n");
        return NULL;
    }
    /*Les coordonn�es de la t�te sont dans le premier maillon*/
    m->co[0]=x;
    m->co[1]=y;
    m->suiv=NULL;
    return m;
}

sec* creer_section(unsigned x, unsigned y){
    /*Description fonction*/
    /*On cr�e le maillon qui servira de t�te du serpent*/
    mai *m=creer_maillon(x,y);

    /*On initialise le struct section*/
    sec *s=malloc(sizeof(sec));

    if (s == NULL) {
        /* Gestion des erreurs d'allocation de m�moire */
        printf("Erreur : Impossible d'allouer de la memoire pour le secteur.\n");
        return NULL;
    }

    s->taille=1;
    s->debut=m;
    s->suiv=NULL;
    s->fin=m;

    return s;
}

ls* creer_liste(unsigned x, unsigned y){
    /*Description fonction*/
    /*On cr�e la section qui servira de t�te du serpent */
    sec *s=creer_section(x,y);
    /*Initialisation du struct liste_section*/
    ls *l=malloc(sizeof(ls));

    if (l == NULL) {
        /* Gestion des erreurs d'allocation de m�moire */
        printf("Erreur : Impossible d'allouer de la memoire pour la liste de secteur.\n");
        return NULL;
    }

    l->lg=1;
    l->debut=s;
    l->fin=s;
    return l;
}


void desallouer_liste(ls *l){
    /*Description fonction*/
    /*on initialise les variables*/

    sec *s=l->debut;
    sec *s2=malloc(sizeof(sec));

    /*On parcours les sections en les vidant */
    while (s->suiv!=NULL){
        s2=s;
        s=s->suiv;
        desallouer_section(s2);
        --l->lg;
    }
    /*Si il n'y a pas de suivant c'est donc la premiere section*/
    desallouer_section(s);
    /*on vide le struct*/
    l->debut=NULL;
    l->fin=NULL;
    --l->lg;

    /*On lib�re la m�moire*/
    free(l);
}




void desallouer_section(sec *s){
    /*Description fonction*/
    /*on initialise les variables*/

    mai *m=s->debut;
    mai *m2;

    /*On parcours les maillons en les vidant */
    while (m->suiv!=NULL){
        m2=m;
        m=m->suiv;
        desallouer_maillon(m2);
        --s->taille;
    }

    /*Si il n'y a pas de suivant c'est donc la premiere section*/
    desallouer_maillon(m);

    /*on vide les champs du struct*/
    s->debut=NULL;
    s->fin=NULL;
    --s->taille;

    /*On lib�re la m�moire*/
    free(s);
}
void desallouer_maillon(mai *m){
    if (m == NULL) {
        return; // Si le maillon est d�j� NULL, pas besoin de le lib�rer.
    }

    /* On vide les champs du maillon*/
    m->suiv=NULL;
    m->co[0]=0;
    m->co[1]=0;

    /*On lib�re la m�moire*/
    free(m);
}



mai* acceder_pos_liste(ls *l, unsigned pos){
    /*Description fonction*/
    mai *m = l->debut->debut;

    while (m != NULL && pos > 0) {
        m = m->suiv;
        pos--;
    }

    return m;
}

void ajouter_section_queue(ls *l, mai *m){
    /*Description fonction*/

    mai *tmp=malloc(sizeof(mai));

    tmp=acceder_pos_liste(l,l->lg-1);
    tmp->suiv=m;
    ++l->lg;

    sec *s=malloc(sizeof(sec));
    s=l->debut;

    while(s->suiv!=NULL){
        s = s->suiv;
    }

    ++s->taille;
    s->fin=m;

    free(s);
    free(tmp);
}




void ajouter_maillon_tete(ls *l,unsigned x, unsigned y,int t){
    /*Description fonction*/


    mai *m=creer_maillon(x,y);
    /*Si t est �gale � 0, le serpent tourne*/
    if (t == 0) { // Si t est �gal � 0, le serpent tourne donc on cr�e une section
        sec *s = malloc(sizeof(sec));
        s->taille = 0;
        s->fin = NULL;
        s->suiv = l->debut;
        s->debut = l->debut->debut;
        l->debut = s;
    }
    // Ajout du nouveau maillon au d�but de la liste
    m->suiv = l->debut->debut;
    l->debut->debut = m;
    l->lg++;
    l->debut->taille++;



}


void supprimer_queue(ls *l){
    /*Description fonction*/

    if(l->debut==NULL){
        return;
    }

    sec *s=l->debut;

    while(s->suiv!=NULL){
        s = s->suiv;
    }

    mai *m=s->debut;

    if(m->suiv==NULL){
        printf("pas de suiv\n");
        desallouer_section(s);
    //il faut supprimer sur la section pr�cedente le fait qu'il y ait un suivant
    }else{
        while (m->suiv->suiv!=NULL){
            m=m->suiv;
        }
        m->suiv=NULL;
    }

    --l->lg;
}

void afficher_ls(ls *l){
    /*Description fonction*/
    sec* s=l->debut;
    mai *m=l->debut->debut;
    int i=0,j=0;
    while(m!=NULL){
        j++;
        m=m->suiv;
    }
    while(s!=NULL){
        i++;
        s=s->suiv;
    }

    printf("il y a %d maillons\n",j);
    printf("Il y a %d sections\n",i);
    printf("la taille de la liste est de :%d\n",l->lg);

}

