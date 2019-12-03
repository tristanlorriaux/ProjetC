#include <stdio.h>
#include "fonctions.h"


int main() {
    simulation(1000);
    tps_rep_moy();
    max_file();
    moyenne_file();
    // pour renommer le txt en .dat
    FILE *file;
    file=fopen("nomfichier.lol", w+);
    rename ("oldname", "newname");
    fclose(file);
    system("start gnuplot -persist -e \"plot 'C:/users/cheminfichier.dat'\"")
    return 0;
   
}
