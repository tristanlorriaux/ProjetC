#include <stdio.h>
#include "fonctions.h"


int main() {
    suppr_fich();
    float temps_simul = 1000;
    simulation(temps_simul);
    float t_moy = tps_rep_moy();
    float max = max_file();
    float moy = moyenne_file();
    // pour renommer le txt en .dat
    FILE *file;
    file=fopen(TXT, "r+");
    rename ("data_file.txt", "data_file.dat");
    fclose(file);
    system("gnuplot -persist -e \"plot '/home/lucasmaisonnave/CLionProjects/projetC/cmake-build-debug/data_file.dat' title 'Nombre de voitures par file' with impulses\"");
    tableau_de_bord(temps_simul,t_moy,max,moy);
    return 0;
}
