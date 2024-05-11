#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include "Liste_section.h"

#ifndef SERPENT_H_
#define SERPENT_H_

typedef struct Serpent
{
    int tete[2];
    ls * l;
    lsm * mov;
    int fruits;
}s;

#endif