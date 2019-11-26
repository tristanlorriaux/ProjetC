#include "fonctions.h"



// PARTIE initialisation
Liste *creation()
{
    /*création d'une liste chaînée vide*/
    Liste *liste = malloc(sizeof(*liste));
    Element *Element = malloc(sizeof(*Element));

    if (liste == NULL || Element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element->voiture.ha=0;
    Element->voiture.t_att=0;
    Element->suiv = NULL;
    liste->premier = Element;
    return liste;
}
/*Liste *initialisation(Liste *liste, int temps_rouge, int temps_init, float lambda){
    insertion(liste, temps_init, temps_rouge);
    float T_I=temps_intermediaire(lambda);

}*/



//---------------------------------------------------------------------------------------------------


//Tristan Aléatoire//


float frand_a_b(float a, float b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

double temps_intermediaire(float lambda, float a, float b){
    float U = frand_a_b(a, b);
    printf ("<<%f>> \n\n",U);
    double X = -log(1 - U )/lambda;
}



//---------------------------------------------------------------------------------------------------

// Partie utilitaire


int convertisseur (int s)//Covertisseur secondes -> heures
{
int m,h,rs;
h=s/3600;
m=s%60;
rs=s%60;
return h,m,rs;
}



void insertion(Liste *liste, float ha) //Insère une voiture à la fin de la file d'attente
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    Element *courant = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->voiture.ha = ha;
    nouveau->voiture.t_att = 0;
    nouveau->voiture.t_passage = 0;
    courant = liste->premier;
    /* Insertion de l'élément à la fin de la liste */
    while (courant->suiv != NULL)
        courant = courant->suiv;
    nouveau->suiv = NULL;
    courant->suiv = nouveau;
}



void avance(Liste *liste){ // Fais avancer la filed'attente de une place (La tête point dorénavant sur la deuxième voiture)
    Element *courant;
    courant = liste->premier;
    courant = courant->suiv;
    liste->premier = courant;
}




int indice_tab(float *tab[N]){
    int i = 0;
    while(tab[i] == 0){
        i++;
    }
}




void ajout_voiture(float timer,Liste *liste, float tab_aleatoire[N]){
    int i = indice_tab(&tab_aleatoire);
    double tps = tab_aleatoire[i];
    Element *nouveau = malloc(sizeof(*nouveau));
    Element *courant = malloc(sizeof(*nouveau));
    courant = liste->premier;
    while (courant->suiv != NULL)
        courant = courant->suiv;
    float der_tps = courant->voiture.ha;
    while((float)tps + der_tps < timer ){
        insertion(liste, (float)tps + der_tps);
        tab_aleatoire[i] = 0;
        i++;
        tps = tab_aleatoire[i];
    }
}


//----------------------------------------------------------------------------------------------------------------
