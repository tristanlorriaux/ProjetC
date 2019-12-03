#include <stdio.h>
#include "fonctions.h"


int main() {
    simulation(5000);
    tps_rep_moy();
    max_file();
    moyenne_file();
    // pour renommer le txt en .dat
    FILE *file;
    file=fopen(NOM_FIC3, "r+");
    rename ("data_file.txt", "data_file.dat");
    fclose(file);
    system("gnuplot -persist -e \"plot '/home/tristan/P_C/cmake-build-debug/data_file.dat' title 'Nombre de voitures par file' with impulses\"");
    return 0;
}
