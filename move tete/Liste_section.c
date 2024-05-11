#include "Liste_section.h"

// Crée un mouvement avec les coordonnées (x, y) et la direction spécifiée
lm* creer_mouvement(int x, int y, enum dir direction) {
    // Allocation de mémoire pour le mouvement
    lm* m = malloc(sizeof(lm));
    if (m == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour le mouvement.\n");
        return NULL;
    }

    // Initialisation des champs du mouvement
    m->coord[0] = x;
    m->coord[1] = y;
    m->direction = direction;
    m->suiv = NULL;

    return m;
}

// Crée une liste de mouvements vide
lsm* creer_liste_mouvement() {
    // Allocation de mémoire pour la liste de mouvements
    lsm* lm = malloc(sizeof(lsm));
    if (lm == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour la liste de mouvements.\n");
        return NULL;
    }

    // Initialisation des champs de la liste de mouvements
    lm->premier = NULL;
    lm->dernier = NULL;
    lm->lg = 0;

    return lm;
}

void desallouer_mouvement(lm **m) {
    if (*m != NULL) {
        // Libération de la mémoire pour le mouvement
        free(*m);
        *m = NULL;
    }
}

void desallouer_liste_mouvement(lsm **lm) {
    if (*lm != NULL) {
        // Initialisation des variables
        lm *current = (*lm)->premier;
        lm *temp;

        // Parcours de la liste de mouvements
        while (current->suiv != NULL) {
            temp = current;
            current = current->suiv;
            // Désallocation du mouvement courant
            desallouer_mouvement(&temp->m);
            // Décrémentation du nombre de mouvements dans la liste
            --(*lm)->lg;
            // Libération de la mémoire pour le maillon courant de la liste de mouvements
            free(temp);
        }

        // Réinitialisation de la liste de mouvements
        (*lm)->premier = NULL;
        (*lm)->dernier = NULL;
        --(*lm)->lg;
        // Libération de la mémoire pour la structure de liste de mouvements elle-même
        free(*lm);
        *lm = NULL;
    }
}

// Ajoute un mouvement à la fin de la liste de mouvements
void ajouter_mvt_fin(lsm *lsm, lm *m) {
    if (lsm != NULL && m != NULL) {
        if (lsm->premier == NULL) {
            // Si la liste est vide, le premier mouvement devient le nouveau mouvement
            lsm->premier = m;
        } else {
            // Sinon, le mouvement est ajouté après le dernier mouvement existant
            lsm->dernier->suiv = m;
        }
        // Le dernier mouvement devient le nouveau mouvement
        lsm->dernier = m;
        // Incrémentation du nombre de mouvements dans la liste
        lsm->lg++;
    }
}


sec* creer_section(unsigned t){
    /*Description fonction*/

    /*Initialisation du struct maillon*/
    sec *s= malloc(sizeof(sec));

    if (s == NULL) {
        /* Gestion des erreurs d'allocation de m�moire */
        printf("Erreur : Impossible d'allouer de la memoire pour le maillon.\n");
        return NULL;
    }
    /*La taille de la section*/
    s->taille=t;
    s->suiv=NULL;
    return s;
}


ls* creer_liste(){
    /*Description fonction*/

    /*Initialisation du struct liste_section*/
    ls *l=malloc(sizeof(ls));

    if (l == NULL) {
        /* Gestion des erreurs d'allocation de m�moire */
        printf("Erreur : Impossible d'allouer de la memoire pour la liste de secteur.\n");
        return NULL;
    }

    l->premier=creer_section(1);
    l->dernier=l->premier;
    l->lg=1;
    return l;
}


void desallouer_liste(ls **l){
    /*Description fonction*/
    /*on initialise les variables*/

    sec *s=(*l)->premier;
    sec *s2=malloc(sizeof(sec));

    /*On parcours les sections en les vidant */
    while (s->suiv!=NULL){
        s2=s;
        s=s->suiv;
        desallouer_section(&s2);
        --(*l)->lg;
    }
    /*Si il n'y a pas de suivant c'est donc la premiere section*/
    desallouer_section(&s);
    /*on vide le struct*/
    (*l)->premier=NULL;
    (*l)->dernier=NULL;
    --(*l)->lg;

    /*On lib�re la m�moire*/
    free(*l);
}




void desallouer_section(sec **s){
    /*Description fonction*/

    /*on vide les champs du struct*/
    (*s)->suiv=NULL;

    /*On lib�re la m�moire*/
    free(*s);
}

int est_vide_liste(const ls *l){
    if(l->premier==NULL || l->lg==0){
        printf("La liste est vide\n");
        return 1;
    }
    return 0;
}


sec* acceder_pos_liste(ls *l, unsigned pos){
    /*Description fonction*/
    sec *s = l->premier;

    while (s != NULL && pos > 0) {
        s = s->suiv;
        pos--;
    }

    return s;
}

void ajouter_sec_fin(ls *l, sec *s){
    /*Description fonction*/    
    ++l->lg;
    l->dernier->suiv=s;
    l->dernier=s;   
}




void ajouter_sec_debut(ls *l,sec *s){
    /*Description fonction*/

    s->suiv=l->premier;
    l->premier=s;
    ++l->lg;
}

sec* extraire_queue (ls *l){
    /*Description fonction*/

    if(l->premier==NULL || l==NULL){
        return NULL;
    }

    sec *tmp=l->premier;
    sec *ex=tmp;

    if(tmp->suiv==NULL){
        printf("Perdu");
        l->premier=NULL;
        ex=tmp;
    }else{
        while(tmp->suiv->suiv!=NULL){
            tmp = tmp->suiv;
        }
        l->dernier=tmp;
        ex=tmp->suiv;
        tmp->suiv=NULL;
    }
    --l->lg;

    return ex;
}



void afficher_ls(const ls *l){
    /*Description fonction*/
    if(l->premier==NULL){
        printf("La liste est vide\n");
        return ;
    }else if(l->premier->suiv==NULL){
        printf("Il n'y a qu'une section de taille %d\n",l->premier->taille);
        return;
    }

    sec* s=l->premier;
    int i=1;
    printf("Il y a %d sections\n",l->lg);
    while(s!=NULL){
        printf("La section n°%d est de taille %d\n",i,s->taille);
        i++;       
        s=s->suiv;
        printf(" TOUR \n");
    }

}

