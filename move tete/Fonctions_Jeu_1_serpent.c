#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"
#include "Grille.h"

void getMenu()
{
    char* title = "SNAKE";
    char* message = "ENTREZ SPACE TO START";
    char* message1 = "ENTREZ Q POUR QUITTER";
    int max_y = getmaxy(stdscr)/2;
    int max_x = getmaxx(stdscr)/2 - strlen(title)/2;
    move(max_y, max_x);
    attron(A_BOLD); //mettre le texte en gras
    printw(title);
    attroff(A_BOLD);
    move(max_y + 9, getmaxx(stdscr)/2 - strlen(message)/2);
    printw(message);
    move(max_y + 12, getmaxx(stdscr)/2 - strlen(message1)/2);
    printw(message1);
}

void choose_mode(int n, int m){
    char * worm = "WORM MODE";
    char * snake = "SNAKE MODE";
    int ch=0;
    do {
        ch = getch();
        int max_y = getmaxy(stdscr)/2;
        int max_x = getmaxx(stdscr)/2 - strlen(worm)/2;
        int max_x1 = getmaxx(stdscr)/2 - strlen(snake)/2;
        move(max_y-4, max_x);
        printw(worm);
        move(max_y+4, max_x1);
        printw(snake);

    } while (ch != '1' && ch!= '2');

    //afficher la grille
    g * grille = Grille_allouer(n, m);
    move_serpent(grille, ch);
}

void move_serpent(g* grille, unsigned mode_chosen)
{
    int ch=0;
    char direction = 'd'; // on stocke la valeur du mouvement 
    s * serpent = malloc(sizeof(s)); // initialise le serpent

    //on le place dans la grille au debut
    serpent->tete[0] = (grille->m)-1; 
    serpent->tete[1] = 0;
    serpent->fruits = 0;
    serpent->l = creer_liste(serpent->tete[0], serpent->tete[1]);
    ajouter_sec_fin(serpent->l, creer_section(1, serpent->tete[0]-1, serpent->tete[1]));

    //on affiche la grille
    draw_Grille(grille, serpent, 1);

    //pour le background
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    wbkgd(stdscr, COLOR_PAIR(1));
    attron(COLOR_PAIR(1));

    while (ch!='q')
    {
        ch = getch();
        if (ch != ERR) {
            switch (ch)
            {
                // pour les mouvements on a wasd, zqsd et les fleches
                case 'w':
                case 'z':
                case KEY_UP: 
                    if(direction != 's') // pour ne pas pouvoir faire un mouvement de haut vers le bas directement 
                        direction = 'w';
                    break;
                case 'a':
                case 'q':
                case KEY_LEFT:
                    if(direction != 'd') // de meme avec les cotes 
                        direction = 'a';
                    break;
                case 's':
                case KEY_DOWN:
                    if(direction != 'w')
                        direction = 's';
                    break;
                case 'd':
                case KEY_RIGHT:
                    if(direction != 'a')
                        direction = 'd';
                    break;
            }
        }
        else {
            switch (direction)
            {
                // si le mouvement est vers le haut on change les coordonnees de la tete pour quelle monte dans la grille et ainsi de suite suivant l input x ou y sera modifie
                case 'w':
                    if (serpent->tete[0] > 0)
                    {
                        serpent->tete[0] -= 1;
                        if(mode_chosen == '2')
                            bouger_corps(serpent);

                    }
                    // et si jamais on ne peut pas avancer cela siginifie qu on est au bord de la grille et on affiche donc un autre ecran 
                    else { 
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
                case 'a':
                    if (serpent->tete[1] > 0)
                    {
                        serpent->tete[1] -= 1;
                        if(mode_chosen == '2')
                            bouger_corps(serpent);
                    }
                    else {
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
                case 's':
                    if (serpent->tete[0] < (grille->n) - 1)
                    {
                        serpent->tete[0] += 1;
                        if(mode_chosen == '2')
                        bouger_corps(serpent);
                    }
                    else {
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
                case 'd':
                    if (serpent->tete[1] < grille->m - 1)
                    {
                        serpent->tete[1] += 1;
                        if(mode_chosen == '2')
                        bouger_corps(serpent);
                    }
                    else {
                        endscreen_loose(serpent);
                        return;
                    }
                    break;
            }
        }

        if (atefruit(grille, serpent) == 1) {
            serpent->fruits+=1;
            ajouter_sec_fin(serpent->l, creer_section(1,serpent->tete[0],serpent->tete[1]));
        }
        
        //if on a le mode worm
        if (mode_chosen == '1')
            bouger_corps(serpent);
        //et pas dans les cases


        clear();
        refresh();
        draw_Grille(grille, serpent, atefruit(grille, serpent));
    }
        
    free(serpent);
}

void endscreen_loose(s* serpent)
{
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1));

    clear();
    refresh();
    printw("BRAVO\n");
    printw("vous avez mange %d fruits", serpent->fruits);
    getMenu();
}

//on regarde si un fruit a ete mange
int atefruit(g* grille, s * serp){
  if (grille->fruit[0] == serp->tete[0] && grille->fruit[1] == serp->tete[1]){
      return 1;     
  }
  return 0;
}


void bouger_corps(s* serpent){
    // pour bouger le reste du corps
        // on veut update les coordonnees a chaque fois 
        sec *current = serpent->l->premier->suiv; // on commence a partir de la deuxieme (1er c la tete)
        // on update les coordonnees de la premiere qui suit la tete  
        serpent->l->premier->coord[1] = serpent->tete[0]; //premiere section correspond a la tete
        serpent->l->premier->coord[0] = serpent->tete[1];
        int prev_x = serpent->tete[0];
        int prev_y = serpent->tete[1];
        while (current != NULL) {
            int tmp_x = current->coord[1];
            int tmp_y = current->coord[0];
                current->coord[1] = prev_x;
                current->coord[0] = prev_y;  
                prev_x = tmp_x;
                prev_y = tmp_y;

            current = current->suiv;
        }
}