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

#define TRUE 1
#define FALSE 0

void synchro_list(char *dossier1, char *dossier2)
{
    int tube1[2] ={-1,-1}, tube2[2]= {-1,-1};
    int pid_fils;

    if(pipe(tube1 )== -1 || pipe(tube2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }


    pid_fils = fork();

     if(pid_fils == 0)//fils 
    {
        close(tube1[1]); // ferme l ecriture, fils lit dans tube1
        close(tube2[0]); // ferme la lecture, fils ecrit dans tube2
        
        char name_file [260];
        char time_file [32];
        char reponse;
        int fichierAcopier = FALSE;
        DIR *d2 = opendir(dossier2); 

        if (d2 != NULL)
        {
            do
            {
               read(tube1[0], &name_file,sizeof(char)*260); //on recupere le nom du fichier du dossier1 courant
                        
                struct dirent *dir;
                while ((dir = readdir(d2)))
                {
                    struct stat st;
                    stat (dir ->d_name,&st);
                    {
                        time_t t = st.st_mtime;           
                        struct tm tm =*localtime(&t);
                        char s[32];
                        strftime(s,sizeof s, " %d/%m/%Y %H:%M:%S ",&tm);

                        if (dir->d_type == DT_REG)
                        {
                            if (strcmp(dir->d_name,name_file )==0) // on compare le nom recuperé avec le nom du fichier courant du dossier2
                            {
                                reponse='o';
                                write(tube2[1], &reponse,sizeof(char)); // on repond que l'on a le meme nom

                                read(tube1[0],&time_file, sizeof(char)*32); //on recupere la date du fichier courant du dossier1

                                if(strcmp(time_file,s)!=0)
                                {
                                    fichierAcopier = TRUE;
                                }

            
                            }
                            else //les noms ne correspondent pas A CHANGER DE PLACE !!!!
                            {
                            reponse ='n';
                            write(tube2[1], &reponse,sizeof(char)); // on repond que l'on a pas le meme nom
    //////////////////////////on copie le fichier grace au fonction faites en TP de systeme
                            }
                        }
                    }       
                }
                //copie fichier si boolean faux -> fichier existe pas 
            }while  (strcmp(name_file,"")!=0);
            closedir(d2);
            
        }
        
        
        
        close(tube1[0]);
        close(tube2[1]);

    }else //pere
    {
        close(tube1[0]); //ferme la lecture, pere ecrit dans tube1
        close(tube2[1]);// ferme l ecriture, pere lit dans tube2

        char reponse;
        DIR *d1 = opendir(dossier1); 
        if (d1 != NULL)
        {
            struct dirent *dir;
            while ((dir = readdir(d1)))
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
                        write(tube1[1],&dir->d_name,sizeof(char)*260);// on transmet le nom du fichier courant du dossier1

                        read(tube2[0], &reponse, sizeof(char)); // on recupere la reponse pour savoir si le fichier existe dans le dossier2

                        if (reponse == 'o')// le fichier existe dans le dossier2
                        {
                            write(tube1[1], &s, sizeof(char)*32);//on transmet la date du fichier courant du dossier1
                        }
                        else if(reponse =='')
                        {

                        }
                    }
                }
                    
            }
            closedir(d1);
        }




        close(tube1[1]);
        close(tube2[0]);
    }
    /*
	
   DIR *rep = opendir (dossier1);
 
   if (rep != NULL)
   {
      struct dirent *lecture;
 
      while ((lecture = readdir (rep)))
      {
         struct stat st;
 
         stat (lecture->d_name, &st);
         {
            time_t t = st.st_mtime;
            struct tm tm = *localtime (&t);
            char s[32];
            strftime (s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
 
            printf ("%-14s %s\n", lecture->d_name, s);
         }
      }
      closedir (rep), rep = NULL;

}
*/
    
    // opendir() renvoie un pointeur de type DIR. 
    
    /*DIR *d2 = opendir(dossier2); 
    if (d2)
    {
        while ((dir = readdir(d2)) != NULL)
        {
			if (dir->d_type == DT_REG)
				printf("%s\n", dir->d_name);
        }
        closedir(d2);
    }*/

}

int main(int argc, char *argv[])
{

    synchro_list(argv[1], argv[2]);      
    return 0;
}

