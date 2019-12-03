#include "fonctions.h"


#define lambda 0.15
#define alpha 1.5
#define T 60                        // période cycle
#define Tv  30                      // période feu vert
#define N 150                       //Taille tableau des Heures d'arrivées
#define NOM_FIC   "data_voit.txt"   //Fichier pour Q3
#define NOM_FIC2   "data_file.txt"  //Fichier pour Q4

// Partie initialisation----------------------------------------------------------------------------------------------------------

Liste *creation()       //Fonction de création d'une liste
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

void ajout_voit_fich(Voiture voit);
int indice_tab(double tab[N]);

//Partie aléatoire -----------------------------------------------------------------------------------------------------

double frand_a_b(float a, float b)      //fonction qui renvoie un flotant entre a et b
{
    return ( (double)rand()/(double)RAND_MAX ) * (b-a) + a;
}

double temps_intermediaire(float a, float b)        //fonction qui renvoie un temps aléatoire pour deux bornes a et b
{
    double U = frand_a_b(a, b);
    double X = -log(1 - U )/lambda;
    return X;
}

void creation_tableau (double tab[N], double der_val)       //fonction qui crée un tableau et qui le remplit de temps aléatoires cumulés
{
    tab[0] = der_val;
    for (int i=1; i<N; i++)
    {
        tab[i] = tab[i-1]+temps_intermediaire(0,1);
    }
}

//Parite statistiques---------------------------------------------------------------------------------------------------


float moyenne_file(void)
{
    FILE *fichier;
    Data data;
    float moyenne;
    float somme = 0;
    int compteur = 0;
    fichier = fopen("data_file.txt", "r+");
    while (fread(&data, sizeof(data), 1, fichier) == 1) {
        somme = somme + data.taille;
        compteur++;
    }
    moyenne = somme / compteur;
    printf("La taille moyenne d'une file d'attente vaut %f", moyenne);
    return compteur;
}

Data max_file(void)
{
    FILE *fichier;
    Data data;
    Data max;
    max.taille=0;
    fichier = fopen("data_file.txt","r+");
    while (fread(&data, sizeof(data), 1, fichier) == 1)
        if (data.taille > max.taille)
            max=data;
    printf("La taille maximale vaut %f", max.taille);
    return max;
}

float tps_rep_moy(void)
{
    FILE *fichier;
    Voiture voiture;
    float somme = 0;
    float cmpt = 0;
    fichier = fopen("data_voiture.txt","r+");
    while (fread(&voiture, sizeof(voiture), 1, fichier) == 1)
    {
        somme += voiture.t_passage + voiture.t_att;
        cmpt++;
    }
    return somme/cmpt;
}



//Partie utilitaire-----------------------------------------------------------------------------------------------------


//Affichage _____________________________________________________________________________________________________

void afficher_tab(double tab[N])        //Fonction qui affiche un tableau
{
    for(int i = 0; i<N; i++)
    {
        printf("%f ",tab[i]);
    }
    printf("\n");
}


void afficher_liste(Liste *liste)       //Fonction qui affiche une liste chaînée
{
    if(liste==NULL)
        exit(EXIT_FAILURE);

    Element *courant = liste->premier;

    while(courant->suiv != NULL)
    {
        courant = courant->suiv;
        printf("%f %f %f %f\n",courant->voiture.indice, courant->voiture.ha,courant->voiture.t_att,courant->voiture.t_passage);
    }
    printf("\n\n");
}


void afficher_Data(Data data)       //Fonction qui affiche une data
{
    printf("taille: %f temps: %f\n", data.taille, data.temps);
}

//Ajout_________________________________________________________________________________________________________

void ajout_file_fich(Liste *liste)      //Fonction qui joute les données utiles à la question 4 d'une file d'attente dans le fichier correspondant
{
    FILE *fic;
    Data data;
    fic = fopen(NOM_FIC2, "a");
    Element *courant;
    courant = liste->premier;
    while (courant->suiv != NULL)       //On récupère la taille de la file et l'heure
    {
        courant = courant->suiv;
    }
    data.taille = courant->voiture.indice;
    data.temps = courant->voiture.ha;
    afficher_Data(data);
    fwrite(&data, sizeof(Data), 1, fic);
    fclose(fic);
}

//OK
void ajout_voit_fich(Voiture voit)      //Fonction qui ajoute les données de la voiture dans un fichier
{
    FILE *fic;
    fic = fopen(NOM_FIC, "a");
    fwrite(&voit, sizeof(Voiture), 1, fic);
    fclose(fic);
}

//OK
void insertion(Liste *liste, float ha, float indice)        //Fonction qui insère une voiture à la fin de la file d'attente
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    Element *courant = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->voiture.ha = ha;
    nouveau->voiture.t_passage = 0;
    courant = liste->premier;
    /* Insertion de l'élément à la fin de la liste */
    while (courant->suiv != NULL)  //On actualise les indices de chaque voiture
        courant = courant->suiv;
    nouveau->suiv = NULL;
    nouveau->voiture.indice = (float)(indice);
    nouveau->voiture.t_passage = ((float)indice)*alpha;    //Temps de passage proportionnel à sont indice dans la file
    courant->suiv = nouveau;
}


void ajout_voiture(float timer,Liste *liste, double tab_aleatoire[N])       //Fonction qui ajoute toutes les voitures qui n'ont pas été ajoutés jusqu'à timer
{
    int i = indice_tab(tab_aleatoire);                                  //indice du premier temps valide de la liste
    float cmpt = 0;
    Element *courant;
    courant = liste->premier;
    while (courant->suiv != NULL)
    {
        courant = courant->suiv;
        cmpt++;
    }
    if (i == N-1)
    {
        creation_tableau(tab_aleatoire,tab_aleatoire[N-1]);
        afficher_tab(tab_aleatoire);
        i = 0;
    }
    double tps = tab_aleatoire[i];                                  //Prochaine Heure d'arivée
    while((float)tps  < timer )
    {                                                               //On insère toutes les voitures qui sont arrivées avant le timer
        insertion(liste, (float)tps, cmpt+1);                       //Insertion de la voiture
        tab_aleatoire[i] = 0;                                       //On supprime le temps d'arrivée de la voiture inseré pour se repérer dans la liste
        i++;                                                        //Indice du prochain temps potentiel à ajouté
        if(i == N-1)
        {
            creation_tableau(tab_aleatoire,tab_aleatoire[N-1]);
            afficher_tab(tab_aleatoire);
            i = 0;
        }
        tps = tab_aleatoire[i];     //temps d'arrivée de la prochaine voiture
        cmpt++;
    }
}
//Fonctions utiles pour les files_______________________________________________________________________________

//OK
void avancer(Liste *liste,float timer)      //Fonction qui fait avancer la filed'attente de une place (La tête pointe dorénavant sur la deuxième voiture)
{
    Element *nouveau = liste->premier;
    if(nouveau->suiv != NULL)
    {
        Element *courant;
        courant = liste->premier;
        courant->voiture.t_att = timer - courant->voiture.ha - courant->voiture.t_passage;      //temps d'attente (temps voiture immobile)
        printf("t_att = %f\n", courant->voiture.t_att);
        ajout_voit_fich(courant->voiture);                                                      //c'est bien le temps passé dans la file - temps de passage
        courant = courant->suiv;

        liste->premier = courant;

        while (courant->suiv != NULL)         //On actualise les indices de chaque voiture
        {
            courant->voiture.indice -= 1;
            courant = courant->suiv;
        }
        courant->voiture.indice -= 1;
    }
}



//OK
int indice_tab(double tab[N])        //Donne l'indice du premier élément qui n'est pas un 0 de la liste
{     
    int i = 0;
    while(tab[i] == 0 && i != N)
    {
        i++;
    }
    return i;
}


float timer_reduit(float timer)     // Fonction qui permet de travailler toujours dans l'intervalle du début
{
    float new_timer = timer;
    while (new_timer >= T)
        new_timer -= T;
    return new_timer;
}



// SIMULATION ----------------------------------------------------------------------------------------------------------

//OK

int simulation(float temps_simul)       //Fonction qui génère une simulation
{
    Liste *File_voitures = creation();
    Liste *File_poubelle = creation();
    float timer = 0;
    double tab_aleatoire[N];
    creation_tableau(tab_aleatoire,temps_intermediaire(0,1));
    afficher_tab(tab_aleatoire);
    printf("\n");
    float timer_red;
    while (timer < temps_simul)
    {
        timer_red = timer_reduit(timer);
        while ((timer_red < Tv - alpha) && (timer < temps_simul))
        {     //Phase 1 : Feu vert
            if((File_voitures->premier)->suiv == NULL)      //Attention au cas où le feu est vert et qu'il n'y a pas de voiture dans la file
            {                 
                printf("V et vide 1");
                timer += Tv-timer_red;
                ajout_voiture(timer,File_poubelle,tab_aleatoire);
                timer_red = timer_reduit(timer);
            }
            else
            {
                timer += (float)alpha;
                avancer(File_voitures,timer);
                ajout_voiture(timer, File_voitures, tab_aleatoire);
                ajout_file_fich(File_voitures);
                timer_red = timer_reduit(timer);
            }
            afficher_liste(File_voitures);
        }
        timer_red = timer_reduit(timer);
        if (((timer_red >= Tv - alpha) && (timer_red <= T)) && (timer < temps_simul))       //Phase 2 : Feu rouge
        {
            if((File_voitures->premier)->suiv == NULL && (timer_red < Tv))
            {
                printf("V et vide 2");
                timer += Tv-timer_red;
                ajout_voiture(timer,File_poubelle,tab_aleatoire);
            }
            else
            {
                timer += T - timer_red;
                ajout_voiture(timer, File_voitures, tab_aleatoire);
                ajout_file_fich(File_voitures);
            }
            afficher_liste(File_voitures);
        }
    }
    return 0;
}
