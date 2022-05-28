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
#define FALSE 0
#define TRUE 1

/*
fctn ecrit dans liste(fichier txt) -> parametre un dossier
    - ouvre un fichier liste.txt
    - ouvre le dossier 
    - compare chaque ligne du fichier avec le fichier courant du dossier
    - si il y est pas on l ajoute
    - si il y est on compare la date  
    - si difference alors on copie la nouvelle date


ftcn synchro list -> parametre 2 dossiers
    ecrit dans liste(dossier1)
    ecrit dans liste (dossier2)
*/

void ajoute_dans_liste(char *dossier)
{
    FILE* fichier = NULL;
    fichier = fopen("liste.txt", "a+");
   
    char ligne [500];
    char nom[260];
    char name_file [260];
    char time_file [32];
    char date_fic[32];
    int fichierExiste = FALSE;

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
            printf("fichier courant de la liste : %s|\n",name_file);
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
                            printf("fichier courant du dossier :%s|\n", dir->d_name);
                            if (strcmp(dir->d_name,name_file )==0) // on compare le nom recuperé avec le nom du fichier courant du dossier2
                            {
                                fichierExiste = TRUE;
                                printf("fichier existe : %s|\n",name_file);
                               // printf("fichier existe\n");
                            }
                        } 
                    }
                }
                if(fichierExiste == FALSE)
                {
                    printf("fichier existe pas \n");
                    char name [1000];
                    strcpy(name , nom);
                    printf("%s \n", name);
                    strcat(name,"-");
                    strcat(name,date_fic);
                    strcat(name,"\n");
                    
                    fputs(name,fichier);
                }
                else
                    fichierExiste=FALSE; 
             closedir(d);
            }  
        }
    }
    fclose(fichier);   
}

int main(int argc, char *argv[])
{
    ajoute_dans_liste(argv[1]);
    return 0;
}
