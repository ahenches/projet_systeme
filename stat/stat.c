#include "manip_fichier.h"
#include "../Logger/logger.h"
#include "./stat.h"




int statistique(){
    logSomething("Récolte données statistiques sur données synchronisation liste");
    int resultat_comparaison = compareDeuxFichiers("./copy_list/ancienne_liste.txt", "./synchro_list/liste.txt");



    

    int nLigneF1 = nombreLignes("./copy_list/ancienne_liste.txt");
    int nLigneF2 = nombreLignes("./synchro_list/liste.txt");

    
    logSomething("Stocker dans un fichier résultat de la collecte d'information");
    appendStrFichier("comparaison_dossier.txt", "ancienne_liste.txt");
    appendValueFichier("comparaison_dossier.txt", nLigneF1);
    appendStrFichier("comparaison_dossier.txt", "liste.txt");
    appendValueFichier("comparaison_dossier.txt", nLigneF2);
    appendStrFichier("comparaison_dossier.txt", "différence");
    appendValueFichier("comparaison_dossier.txt", resultat_comparaison);
    appendTermlineFichier("comparaison_dossier.txt");

    return 0;
}