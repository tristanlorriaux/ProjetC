#include "fonctions_init.h"
#include "setup.h"


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





