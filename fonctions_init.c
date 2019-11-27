#include "fonctions_init.h"



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


//Partie Aléatoire//


float frand_a_b(float a, float b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

double temps_intermediaire(float lambda, float a, float b){
    float U = frand_a_b(a, b);
    double X = -log(1 - U )/lambda;
    return X;
}

void creation_tab_aleatoire(double *tab_aleatoire[N]){
    for(int i = 0; i<N; i++){
        tab_aleatoire[i] = temps_intermediaire(lambda, 0.0, 1.0)
    }
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



void avancer(Liste *liste){ // Fais avancer la filed'attente de une place (La tête point dorénavant sur la deuxième voiture)
    Element *courant;
    courant = liste->premier;
    courant = courant->suiv;
    liste->premier = courant;
}




int indice_tab(float *tab[N]){  //Donne l'indice du premier élément qui n'est pas un 0 de la liste
    int i = 0;
    while(tab[i] == 0){
        i++;
    }
}




void ajout_voiture(float timer,Liste *liste, float tab_aleatoire[N]){   //Ajoute toutes les voitures qui n'ont pas étaient ajoutés jusqu'à timer
    int i = indice_tab(&tab_aleatoire);             //indice du premier temps valide de la liste
    double tps = tab_aleatoire[i];                  //prochain temps aléatoire
    Element *nouveau = malloc(sizeof(*nouveau));
    Element *courant = malloc(sizeof(*nouveau));
    courant = liste->premier;
    while (courant->suiv != NULL)
        courant = courant->suiv;
    if (tab_aleatoire[-1] == 0){                    //SI le tableau est vide on en recalcule un nouveau
                creation_tab_aleatoire(tab_aleatoire);
            }
    float der_tps = courant->voiture.ha;            //temps d'arrivée de la dernière voiture
    while((float)tps + der_tps < timer ){           //On insère toutes les voiture qui sont arrivées avantle timer tps + der_tps = ha dernière voiture
        insertion(liste, (float)tps + der_tps);     //INsertion de la voiture
        tab_aleatoire[i] = 0;                       //On supprive le temps d'arrivée de la voiture inseré pour se repérer dans la liste
        i++;                                        //INdice du prochain temps potentiel à ajouté
        der_tps+=(float)tps                         //Heure d'arrivée de la nouvelle voiture ajouté
        tps = tab_aleatoire[i];                     //temps d'arrivée de la prochaine voiture
    }
}

float timer_reduit(float timer)// permet de travailler toujours dans l'intervalle du début
{
    float new_timer;
    while (timer>T)
        new_timer = timer-T;
    return new_timer;
}

void simulation(float temps_simul){
    Liste *File_voitures=creation();
    float timer=0;
    float tab_aleatoire[N];
    creation_tab_aleatoire(tab_aleatoire);
    float timer_red = timer_reduit(timer);
    while (timer<temps_simul){        
        
        timer_red = timer_reduit(timer);
        
        while (timer_red < Tv-alpha && timer_red > 0 && timer < temps_simul){   //Phase 1 : Feu vert
            avancer(File_voitures);
            timer+=alpha;            
            ajout_voiture(timer,File_voitures,tab_aleatoire);
            timer_red = timer_reduit(timer);
        }              
        
        
        timer_red = timer_reduit(timer);
        while (timer_red >= Tv - alpha && timer_red <= Tv && timer < temps_simul){                          //Phase 2 : Moment où le feu 
            timer +=  Tv - timer_red                            //On ajoute l'écart entre le temps Tv       //est vert mais les voitures n'auront pas le temps de passer le feu
            ajout_voiture(timer,File_voitures,tab_aleatoire);  //(passage au rouge) et le timer modulo T
            timer_red = timer_reduit(timer);
        }
        
        
        timer_red = timer_reduit(timer);
        while(timer_red >= Tv  && timer_red <= T && timer < temps_simul)    //Phase 3 : Feu rouge            
            
            ajout_voiture(timer,File_voitures,tab_aleatoire);
        
            timer +=  T - timer_red;                                //On ajoute avant et après la mise à jour
                                                                    // du timer en prévention d'un cas particulier un peu chiant, si alpha est tel que l'on saute la phase 2
            ajout_voiture(timer,File_voitures,tab_aleatoire);
            timer_red = timer_reduit(timer);
    }
   
}










//----------------------------------------------------------------------------------------------------------------
