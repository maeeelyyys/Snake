#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Grille.c"
#include "Liste_section.c"
#include "Serpent.c"

int main()
{
    srand(time(NULL));
    int n = 7;
    int m = 4;
    g * grille_test = Grille_allouer(n, m);
    Grille_vider(grille_test);
    Grille_redessiner(grille_test);
}
