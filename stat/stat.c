#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "manip_fichier.c"



    // int h, min, s, day, mois, an;
    // time_t now;

    // // Renvoie l'heure actuelle
    // time(&now);
    // // Convertir au format heure locale
    // printf("Aujourd'hui est : %s", ctime(&now));
    // struct tm *local = localtime(&now);
    // h = local->tm_hour;
    // min = local->tm_min;
    // s = local->tm_sec;
    // day = local->tm_mday;
    // mois = local->tm_mon + 1;
    // an = local->tm_year + 1900;
    // printf("L'heure : %02d:%02d:%02d\n", h, min, s);
    // // Afficher la date courante
    // printf("La date : %02d/%02d/%d\n", day, mois, an);


int main(){

    int resultat_comparaison = compareDeuxFichiers("../copy_list/ancienne_liste.txt", "../synchro_list/liste.txt");



 

    int nLigneF1 = nombreLignes("../copy_list/ancienne_liste.txt");
    int nLigneF2 = nombreLignes("../synchro_list/liste.txt");


    appendStrFichier("comparaison_dossier.txt", "ancienne_liste.txt");
    appendValueFichier("comparaison_dossier.txt", nLigneF1);
    appendStrFichier("comparaison_dossier.txt", "liste.txt");
    appendValueFichier("comparaison_dossier.txt", nLigneF2);
    appendStrFichier("comparaison_dossier.txt", "différence");
    appendValueFichier("comparaison_dossier.txt", resultat_comparaison);
    appendTermlineFichier("comparaison_dossier.txt");







    return 0;
}