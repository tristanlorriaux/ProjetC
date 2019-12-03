#include <stdio.h>
#include "fonctions.h"


int main() {
    float temps_simul=5000;
    simulation(temps_simul);
    float a = tps_rep_moy();
    float b = max_file();
    float c = moyenne_file();
    // pour renommer le txt en .dat
    FILE *file;
    file=fopen(NOM_FIC3, "r+");
    rename ("data_file.txt", "data_file.dat");
    fclose(file);
    system("gnuplot -persist -e \"plot '/home/tristan/P_C/cmake-build-debug/data_file.dat' title 'Nombre de voitures par file' with impulses\"");
    tableau_de_bord(temps_simul,a,b,c);
    return 0;
}
