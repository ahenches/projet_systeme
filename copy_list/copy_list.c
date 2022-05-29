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
#include "../synchro_list/synchro_list.h"
#include "./copy_list.h"

void copie_fichier(char *fichier1, char *fichier2)
{

    FILE* liste = NULL;
    FILE* copieListe = NULL;
	char* contenu = NULL;
	char tmp[TAILLE_TAMPON]="";

	liste = fopen(fichier1,"r");

	if(liste != NULL)
	{
		contenu = (char*)malloc(1*sizeof(char));
		contenu[0]='\0';

		//Lecture ligne à ligne du contenu du fichier
		while( fgets(tmp,TAILLE_TAMPON,liste) )
		{
			contenu = (char*)realloc(contenu,(strlen(contenu)+strlen(tmp)+1)*sizeof(char));
			strcpy(contenu+strlen(contenu),tmp);
		}
	}
	fclose(liste);

	copieListe = fopen(fichier2, "w");

	if(copieListe != NULL && contenu!=NULL)
	{
		fputs(contenu, copieListe);
	}

    fclose(copieListe);
    free(contenu);
}

void compare_listes()
{
    char ligne [500];
    char ligne2 [500];
    char nom[260];
    char name_file [260];
    char time_file [32];
    char date_fic[32];
    int fichierAjoute = TRUE;
    int fichierModifie = FALSE;
    FILE* liste = NULL;

    liste = fopen("../synchro_list/liste.txt", "r");
    if (liste!= NULL )
    {
        while(fgets(ligne,sizeof(char)*500, liste))
        {
            char *resultatDecoupe = strtok(ligne, "-");
            for (int i =0; i<2; i++)
            {
                if (i==0)
                    strcpy(name_file,resultatDecoupe);
                else 
                    strcpy(time_file,resultatDecoupe);
                resultatDecoupe=strtok(NULL,"-");
            }
            FILE* ancienne_liste = NULL;
            ancienne_liste = fopen("./ancienne_liste.txt","r");
            while(fgets(ligne2,sizeof(char)*500, ancienne_liste))
            {               
                char *resultatDecoupe2 = strtok(ligne2, "-");
                for (int i =0; i<2; i++)
                {
                    if (i==0)
                        strcpy(nom,resultatDecoupe2);
                    else 
                        strcpy(date_fic,resultatDecoupe2);
                    resultatDecoupe2=strtok(NULL,"-");
                }
                if (strcmp(nom,name_file )==0) 
                {
                    fichierAjoute = FALSE;
                    
                    if(strcmp(time_file,date_fic)!=0)
                    {
                        fichierModifie = TRUE;
                    }
                }
            }
            if(fichierAjoute == TRUE || fichierModifie == TRUE)
            {
                char fichier_a_copier [1000];
                char fichier_copie [1000];
                strcpy(fichier_a_copier, SERVEUR1);
                strcat(fichier_a_copier,"/");
                strcat(fichier_a_copier, name_file);

                strcpy(fichier_copie, SERVEUR3);
                strcat(fichier_copie,"/");
                strcat(fichier_copie, name_file);
                copie_fichier(fichier_a_copier,fichier_copie);
            }
            fichierAjoute = TRUE;
            fichierModifie = FALSE;
            fclose(ancienne_liste);
        }
    }
    fclose(liste);


}


void copy_list()
{
    copie_fichier("../synchro_list/liste.txt","./ancienne_liste.txt");
    synchro_list(SERVEUR1,SERVEUR2);
    compare_listes();
}

