#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>

#define lambda 6
#define alpha 3
#define T 10   // periode cycle
#define Tv 6   // temps passage au vert
#define N 1000



/*
 * #ifndef PROJET_C_FONCTIONS_H
#define PROJET_C_FONCTIONS_H

#endif //PROJET_C_FONCTIONS_H
 */

typedef struct{
    float ha;
    float t_att;
    float t_passage;
}Voiture;


typedef struct Element Element;
struct Element
{
    Voiture voiture;
    Element *suiv;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};
