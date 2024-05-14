#include <stdio.h>
#include <time.h>   
#include <string.h>
#include <ncurses.h>
#include "Fonctions_Jeu.h"
#include "Grille.h"

void getMenu()
{
    show_title();
    int max_y = getmaxy(stdscr)/2 -10;
    char* message = "ENTREZ SPACE TO START";
<<<<<<< HEAD
    char* message1 = "ENTREZ Q POUR QUITTER";
    int max_y = getmaxy(stdscr)/2;
    int max_x = getmaxx(stdscr)/2 - strlen(title)/2;
    move(max_y, max_x);
    attron(A_BOLD);
    printw("%s",title);
    attroff(A_BOLD);
    move(max_y + 9, getmaxx(stdscr)/2 - strlen(message)/2);
    printw("%s",message);
    move(max_y + 12, getmaxx(stdscr)/2 - strlen(message1)/2);
    printw("%s",message1);
=======
    move(max_y +15, getmaxx(stdscr)/2 - strlen(message)/2);
    printw(message);
>>>>>>> 0f1235274571753e3d3afc5da82ed4e63e8f8f44
}

void choose_mode(int n, int m){
    char *worm = "WORM MODE";
    char *snake = "SNAKE MODE";
    char *texte  = "- press 1 -";
    char *texte1 = "- press 2 -";
    
    int ch = 0;
    do {
        ch = getch();
<<<<<<< HEAD
        int max_y = getmaxy(stdscr)/2;
        int max_x = getmaxx(stdscr)/2 - strlen(worm)/2;
        int max_x1 = getmaxx(stdscr)/2 - strlen(snake)/2;
        move(max_y-4, max_x);
        printw("%s",worm);
        move(max_y+4, max_x1);
        printw("%s",snake);
=======
>>>>>>> 0f1235274571753e3d3afc5da82ed4e63e8f8f44

        // Clear the screen
        clear();
        show_title();
        // Calculate the positions for each text
        int max_y = getmaxy(stdscr) / 2;
        int max_x_worm = getmaxx(stdscr) / 2 - strlen(worm) - strlen(texte) / 2;
        int max_x_snake = getmaxx(stdscr) / 2 + strlen(texte) / 2;
        int max_x_texte = getmaxx(stdscr) / 2 - strlen(texte) / 2 - strlen(texte1) ;

        // Print "WORM MODE"
        attron(A_STANDOUT);
        mvprintw(max_y +4, max_x_worm -10, worm);
        attroff(A_STANDOUT);

        // Print "- press 1 -"
        attron(A_BLINK);
        mvprintw(max_y +6, max_x_texte -9, texte);
        attroff(A_BLINK);
        // Print "SNAKE MODE"
        attron(A_STANDOUT);
        mvprintw(max_y +4, max_x_snake +10, snake);
        attroff(A_STANDOUT);

        // Print "- press 2 -"
        attron(A_BLINK);
        mvprintw(max_y +6, getmaxx(stdscr) / 2 + strlen(texte) / 2 +9, texte1);
        attroff(A_BLINK);

    } while (ch != '1' && ch != '2' && ch != 'q');
    if (ch == 'q')
    {
        clear();
        refresh();
        getMenu();
    }
    else
    {
        clear();
        refresh();
        //afficher la grille
        g * grille = Grille_allouer(n, m);
        if(ch == '2')
            grille->couleur_snake = 4; //couleur par defaut du serpent
        else
            grille->couleur_snake = 9; //couleur par defaut du worm
        move_serpent(grille, ch);
    }
    
}

void move_serpent(g* grille, unsigned mode_chosen)
{

    char direction = 'd'; // on stocke la valeur du mouvement 
    s * serpent = malloc(sizeof(s)); // initialise le serpent
    int ch=0;
    //on le place dans la grille au debut

    serpent->tete[0] = (grille->m)-1; 
    serpent->tete[1] = 0;
    serpent->fruits = 0;
    serpent->l = creer_liste(serpent->tete[0], serpent->tete[1]);
    ajouter_sec_fin(serpent->l, creer_section(1, serpent->tete[0]-1, serpent->tete[1]));

    //on affiche la grille
<<<<<<< HEAD
    draw_Grille(grille, serpent, 1);
=======
    draw_Grille(grille, serpent, 1, mode_chosen);

>>>>>>> 0f1235274571753e3d3afc5da82ed4e63e8f8f44
    //pour le background

    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    attron(COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1));
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
                            bouger_corps(serpent, mode_chosen, grille);

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
                            bouger_corps(serpent, mode_chosen, grille);
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
                            bouger_corps(serpent, mode_chosen, grille);
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
                            bouger_corps(serpent, mode_chosen, grille);
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
<<<<<<< HEAD
            ajouter_sec_fin(serpent->l, creer_section(1,serpent->tete[0], serpent->tete[1]));
=======
            ajouter_sec_fin(serpent->l, creer_section(1,serpent->tete[0],serpent->tete[1]));
            if(mode_chosen == '2')
                grille->couleur_snake = grille->couleur_fruit;
>>>>>>> 0f1235274571753e3d3afc5da82ed4e63e8f8f44

        }
        
        //if on a le mode worm
        if (mode_chosen == '1')
            bouger_corps(serpent, mode_chosen, grille);
        //et pas dans les cases


        clear();
        refresh();
<<<<<<< HEAD
        draw_Grille(grille, serpent, atefruit(grille, serpent));
        
=======
        draw_Grille(grille, serpent, atefruit(grille, serpent), mode_chosen);
>>>>>>> 0f1235274571753e3d3afc5da82ed4e63e8f8f44
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
    printw("vous avez mange %d fruits", serpent->fruits);
    printw("BRAVO\n");
    getMenu();
}

//on regarde si un fruit a ete mange
int atefruit(g* grille, s * serp){
  if (grille->fruit[0] == serp->tete[0] && grille->fruit[1] == serp->tete[1]){
      return 1;     
  }
  return 0;
}


void bouger_corps(s* serpent, unsigned mode_chosen, g * grille){
    // pour bouger le reste du corps
<<<<<<< HEAD
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
=======
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

void show_title(){
    char* title[] = {
        "   SSSSS   N     N    A    K   K  EEEEE",
        "  S        NN    N   A A   K  K   E    ",
        "   SSS     N N   N  AAAAA  KKK    EEEE ",
        "      S    N  N  N  A   A  K  K   E    ",
        "  SSSSS    N   N N  A   A  K   K  EEEEE"
    };
      /*" ██████╗ ███╗   ██╗ █████╗   ██╗  ██╗  ██████╗",
        "██╔════╝ ████╗  ██║ ██╔══██╗ ██║ ██╔╝ ██╔════╝",
        "███████╗ ██╔██╗ ██║ ███████║ ███████║ ███████╗",
        "╚════██║ ██║╚██╗██║ ██╔══██║ ██╔══██║ ██╔════╝",
        "███████║ ██║ ╚ ███║ ██║  ██║ ██║  ██║ ███████║",
        "╚══════╝ ╚═╝  ╚═══╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝ ╚══════╝"
    */
    int i;
    int max_y = getmaxy(stdscr)/2 -10;
    for(i=0; i< 5; i++)
    {
        int max_x = getmaxx(stdscr)/2 - strlen(title[i])/2;
        move(max_y + i, max_x);
        attron(A_BOLD ); //mettre le texte en gras
        printw(title[i]);
        attroff(A_BOLD);
    }
    char* message1 = "ENTREZ Q POUR QUITTER";
    move(max_y + 20, getmaxx(stdscr)/2 - strlen(message1)/2);
    printw(message1);
>>>>>>> 0f1235274571753e3d3afc5da82ed4e63e8f8f44
}