//
// Created by lucasmaisonnave on 04/12/2019.
//

#ifndef PROJETC_FONCTIONS_H
#define PROJETC_FONCTIONS_H

#endif //PROJETC_FONCTIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>


#define lambda 0.28
#define alpha 1.8
#define T 60.0                      // période cycle
#define Tv  30.0                     // période feu vert
#define N 150                       //Taille tableau des Heures d'arrivées
#define NOM_FIC   "data_voit.bin"   //Fichier pour Q3
#define NOM_FIC2   "data_file.dat"  //Ficahier pour Q4
#define NOM_FIC3   "data_file.txt"  //Fichier pour Q5


typedef struct{
    float indice;
    float ha;
    float t_att;
    float t_passage;
} Voiture;


typedef struct
{
    float taille;
    float temps;
} Data;


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


Liste *creation();
double frand_a_b(float a, float b);
double temps_intermediaire(float a, float b);
void creation_tableau (double tab[N], double der_val);
void afficher_tab(double tab[N]);
void afficher_liste(Liste *liste);
//int convertisseur (int s);//
void insertion(Liste *liste, float ha, float indice);
void avancer(Liste *liste, float timer);
int indice_tab(double tab[N]);
void ajout_voiture(float timer,Liste *liste, double tab_aleatoire[N]);
float timer_reduit(float timer);
int simulation(float temps_simul);
float tps_rep_moy(void);
float max_file(void);
float moyenne_file(void);
void ajout_file_fichtxt(Liste *liste);
void tableau_de_bord(float T_simu, float tps_rep_moy, float max, float moyenne);
