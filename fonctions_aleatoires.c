#include "fonctions_aleatoires.h"
#include "setup.h"


float frand_a_b(float a, float b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

double temps_intermediaire(float lambda, float a, float b){
float U = frand_a_b(a, b);
double X = -log(1 - U )/lambda;
return X;
}
