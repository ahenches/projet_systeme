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
#include "./synchro_list.h"

void ajoute_dans_liste(char *dossier)
{
    char ligne [500];
    char nom[260];
    char name_file [260];
    char time_file [32];
    char date_fic[32];
    int fichierExiste = FALSE;

    DIR *d = opendir(dossier);
    if (d != NULL)
    {
        struct dirent *dir;
        while ((dir = readdir(d)))
        {
            struct stat st;
            stat (dir ->d_name,&st);
            {
                time_t t = st.st_mtime;        
                struct tm tm =*localtime(&t);
                char s[32];
                strftime(s,sizeof s, "%d/%m/%Y %H:%M:%S",&tm);
                strcpy(date_fic,s);
                strcpy(nom, dir->d_name);
                if (dir->d_type == DT_REG)
                {
                    FILE* fichier = NULL;
                    fichier = fopen("../synchro_list/liste.txt", "a+");
                    if (fichier!= NULL )
                    {
                        while(fgets(ligne,sizeof(char)*500, fichier))
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
                            if (strcmp(dir->d_name,name_file )==0) // on compare le nom recuperé avec le nom du fichier courant du dossier2
                            {
                                fichierExiste = TRUE;
                            }
                        }
                        if(fichierExiste == FALSE)
                        {
                            char name [1000];
                            strcpy(name , nom);
                            strcat(name,"-");
                            strcat(name,date_fic);
                            strcat(name,"\n");
                            fputs(name,fichier); 
                        }
                        else
                            fichierExiste = FALSE;
                    }
                    fclose(fichier);
                } 
            }
        }
    }
    closedir(d);
}


void actualise_liste(char *dossier)
{
    FILE* fichier = NULL;
    fichier = fopen("../synchro_list/liste.txt", "w");

    if (fichier!= NULL )
    {
        DIR *d = opendir(dossier);
        if (d != NULL)
        {
            struct dirent *dir;
            while ((dir = readdir(d)))
            {
                struct stat st;
                stat (dir ->d_name,&st);
                {
                    time_t t = st.st_mtime;        
                    struct tm tm =*localtime(&t);
                    char s[32];
                    strftime(s,sizeof s, "%d/%m/%Y %H:%M:%S",&tm);
                    if (dir->d_type == DT_REG)
                    {
                        char name [1000];
                        strcpy(name , dir->d_name);
                        strcat(name,"-");
                        strcat(name,s);
                        strcat(name,"\n");
                        fputs(name,fichier);
                    }
                }
            }
        }
        closedir(d);
    }
    fclose(fichier);
}

void synchro_list(char *dossier1, char *dossier2)
{   
    actualise_liste(dossier1);
    ajoute_dans_liste(dossier2);
}
