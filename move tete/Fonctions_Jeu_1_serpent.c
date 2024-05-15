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
    move(max_y +15, (getmaxx(stdscr)+1)/2 - strlen(message)/2);
    printw("%s",message);
}

void choose_mode(int n, int m){

    //lists with the different modes and texts below it 
    char *modes[] = {"WORM MODE", "SNAKE MODE", "TWO PLAYERS MODE"};
    char *text[] = {"- press 1 -", "- press 2 -", "- press 3 -"};

    int num_modes = sizeof(modes) / sizeof(modes[0]);
    
    int ch = 0;
    do {
        ch = getch();

        // Clear the screen
        refresh();
        //show the title 
        show_title();
        //calculate middle of the screen
        int max_y = getmaxy(stdscr) / 2;
        int max_x = getmaxx(stdscr) / 2;
        int space_btw =10; // is the space between modes

        // Calculate the position at the start 
        int start_x = max_x - (strlen(modes[0])/2 + strlen(modes[1])/2 + strlen(modes[2])/2 + space_btw);

        //for each mode and corresponding text
        for (int i = 0; i < num_modes; i++) {
            //position for the current mode being printed
            int mode_x = start_x + i * (strlen(modes[0]) + space_btw); 

            //print the mode
            attron(A_STANDOUT);
            mvprintw(max_y, mode_x, "%s", modes[i]);
            attroff(A_STANDOUT);

            //position for the text below
            int text_x = mode_x + (strlen(modes[i]) - strlen(text[i])) / 2;

            // Print the text
            attron(A_BLINK);
            mvprintw(max_y + 2, text_x, "%s", text[i]);
            attroff(A_BLINK);
        }

    } while (ch != '1' && ch != '2' && ch != '3' && ch != 'f');
    if (ch == 'f')
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
        if(ch == '2' || ch == '3')
            grille->couleur_snake = 4; //couleur par defaut du serpent
        else if (ch == '1')
            grille->couleur_snake = 9; //couleur par defaut du worm
        move_serpent(grille, ch);
    }
    
}

void move_serpent(g* grille, unsigned mode_chosen)
{

    char direction = 'd'; // on stocke la valeur du mouvement
    char direction2 = 'd';
    s * serpent = malloc(sizeof(s)); // initialise le serpent
    s * serpent2 = malloc(sizeof(s));
    int ch=0;
    //on le place dans la grille au debut

    serpent->tete[0] = (grille->m)-1; 
    serpent->tete[1] = 0;
    serpent->fruits = 0;
    serpent->l = creer_liste(serpent->tete[0], serpent->tete[1]);
    ajouter_sec_fin(serpent->l, creer_section(1, serpent->tete[0], serpent->tete[1]));

    if(mode_chosen == '3')
    {
        serpent2->tete[0] = 0;
        serpent2->tete[1] = (grille->n) - 1;
        serpent2->fruits = 0;
        serpent2->l = creer_liste(serpent2->tete[0], serpent2->tete[1]);
        ajouter_sec_fin(serpent2->l, creer_section(1, serpent2->tete[0], serpent2->tete[1]));
    }
    //on affiche la grille
    draw_Grille(grille, serpent, 1, mode_chosen, serpent2);

    //pour le background
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    attron(COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1));
    while (ch!='f')
    {
        ch = getch();
        if (ch != ERR) {
            direction = mov_one_player(ch, direction);
            if(mode_chosen == '3')
                direction2 = mov_two_player(ch, direction2);
        }
        else {
            if (move_serpent_direction(grille, serpent, direction,  mode_chosen) == 1 && (mode_chosen == '2' || mode_chosen == '3'))
            {
                endscreen_loose(serpent);
                break;

            }
        }

        if (atefruit(grille, serpent) == 1) {
            serpent->fruits+=1;
            ajouter_sec_fin(serpent->l, creer_section(1,serpent->tete[0],serpent->tete[1]));
            if(mode_chosen == '2')
                grille->couleur_snake = grille->couleur_fruit;
            if(serpent->fruits==(grille->n*grille->m)){
                endscreen_win(serpent);
                return;
            }

        }
        
        //if on a le mode worm
        if (mode_chosen == '1')
        {
            bouger_corps(serpent, grille);
            
        }
        //et pas dans les cases

        refresh();
        clear();
        draw_Grille(grille, serpent, atefruit(grille, serpent), mode_chosen, serpent2);

    }
        
    free(serpent);
    free(serpent2);
}

void endscreen_loose(s* serpent)
{
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1));

    clear();
    refresh();
    fflush(stdout);
    printw("Dommage, vous avez mange %d fruits, vous etiez si proche !", serpent->fruits);
    getMenu();
}

void endscreen_win(s* serpent){
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1));
    //peut etre ne faire qu'une seule fonction et en fonction du nombre de fruit mangé
    //on sait si le joueur ) gagner ou non
    clear();
    refresh();
    printw("Félicitation ");
    getMenu();

}


//on regarde si un fruit a ete mange
int atefruit(g* grille, s * serp){
  if (grille->fruit[0] == serp->tete[0] && grille->fruit[1] == serp->tete[1]){
      return 1;     
  }
  return 0;
}


void bouger_corps(s* serpent, g * grille){
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


int move_serpent_direction(g* grille, s* serpent, char direction, unsigned mode_chosen) {
    switch (direction) {
        case 'w':
            return move_serpent_up(grille, serpent, mode_chosen);
            break;
        case 'a':
            return move_serpent_left(grille, serpent, mode_chosen);
            break;
        case 's':
            return move_serpent_down(grille, serpent, mode_chosen);
            break;
        case 'd':
            return move_serpent_right(grille, serpent, mode_chosen);
            break;
    }
}

int move_serpent_up(g* grille, s* serpent, unsigned mode_chosen) {

    if (mode_chosen == '1') {
        if (serpent->tete[0] == 0)
            serpent->tete[0] = grille->n - 1;
        else
            serpent->tete[0]--;
        return 1;
    }
    if (serpent->tete[0] > 0) {
        if ((mode_chosen == '2' || mode_chosen == '3')  && is_collision(grille, serpent->tete[0] - 1, serpent->tete[1], mode_chosen))
            return 1;
        serpent->tete[0]--;
        if ((mode_chosen == '2' || mode_chosen == '3') )
        {
            bouger_corps(serpent, grille);
            return 0;
        }
    }
    return 1;
}

int move_serpent_left(g* grille, s* serpent, unsigned mode_chosen) {
    if (mode_chosen == '1') {
        if (serpent->tete[1] == 0)
            serpent->tete[1] = grille->m - 1;
        else
            serpent->tete[1]--;
        return 1;
    }
    if (serpent->tete[1] > 0) {
        if ((mode_chosen == '2' || mode_chosen == '3')  && is_collision(grille, serpent->tete[0], serpent->tete[1] - 1, mode_chosen))
            return 1;
        serpent->tete[1]--;
        if ((mode_chosen == '2' || mode_chosen == '3') )
        {
            bouger_corps(serpent, grille);
            return 0;
        }
    }
    return 1;
}

int move_serpent_down(g* grille, s* serpent, unsigned mode_chosen) {
    if (mode_chosen == '1') {
        if (serpent->tete[0] == grille->n - 1)
            serpent->tete[0] = 0;
        else
            serpent->tete[0]++;
        return 1;
    }
    if (serpent->tete[0] < grille->n - 1) {
        if ((mode_chosen == '2' || mode_chosen == '3')  && is_collision(grille, serpent->tete[0] + 1, serpent->tete[1], mode_chosen))
            return 1;
        serpent->tete[0]++;
        if ((mode_chosen == '2' || mode_chosen == '3') )
        {
            bouger_corps(serpent, grille);
            return 0;
        }
    }
    return 1;
}

int move_serpent_right(g* grille, s* serpent, unsigned mode_chosen) {
    if (mode_chosen == '1') {
        if (serpent->tete[1] == grille->m - 1)
            serpent->tete[1] = 0;
        else
            serpent->tete[1]++;
        return 1;
    }
    if (serpent->tete[1] < grille->m - 1) {
        if ((mode_chosen == '2' || mode_chosen == '3')  && is_collision(grille, serpent->tete[0], serpent->tete[1] + 1, mode_chosen))
            return 1;
        serpent->tete[1]++;
        if ((mode_chosen == '2' || mode_chosen == '3') )
        {
             bouger_corps(serpent, grille);
             return 0;
        }
    }
    return 1;
}

int is_collision(g* grille, int x, int y, unsigned mode_chosen) {

    // coordinates collide with any body segment
    if ((mode_chosen == '2' || mode_chosen == '3') && strcmp(grille->tab[x][y]->elem, "body") == 0)
        return 1; // collision with body
    //coordinates are within the grid boundaries
    if (x < 0 || y < 0 || x >= grille->n || y >= grille->m) {
        clear();
        refresh();
        return 1; // collision with border
    }

    return 0; // no collision
}

char mov_one_player(int ch, char direction)
{
    if (ch != ERR) {
        switch (ch)
        {
    // pour les mouvements on a wasd, zqsd 
                case 'w':
                case 'z':
                    if(direction != 's') // pour ne pas pouvoir faire un mouvement de haut vers le bas directement 
                        return 'w';
                    break;
                case 'a':
                case 'q':
                    if(direction != 'd') // de meme avec les cotes 
                        return'a';
                    break;
                case 's':
                    if(direction != 'w')
                        return 's';
                    break;
                case 'd':
                    if(direction != 'a')
                        return 'd';
                    break;
        }
    }
    return direction;
}
char mov_two_player(int ch, char direction2)
{
    if (ch != ERR) {
        switch (ch)
        {
    // pour les mouvements on a les fleches
                case KEY_UP:
                    if(direction2 != 's') 
                        return 'w';
                    break;
                case KEY_LEFT:
                    if(direction2 != 'd') 
                        return 'a';
                    break;
                case KEY_DOWN:
                    if(direction2 != 'w') 
                        return 's';
                    break;
                case KEY_RIGHT:
                    if(direction2 != 'a') 
                        return 'd';
                    break;
        }
    }
    return direction2;
}


void show_title(){
    char* title[] = {
        "   SSSS    N     N    A    K   K  EEEEE",
        "  S        NN    N   A A   K  K   E    ",
        "   SSS     N N   N  AAAAA  KKK    EEEE ",
        "      S    N  N  N  A   A  K  K   E    ",
        "  SSSS     N   N N  A   A  K   K  EEEEE"
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
        printw("%s",title[i]);
        attroff(A_BOLD);
    }
    char* message1 = "ENTREZ F POUR FERMER";
    move(max_y + 20, (getmaxx(stdscr)+1)/2 - strlen(message1)/2);
    printw("%s",message1);
}