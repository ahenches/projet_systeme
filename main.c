#include "./copy_list/copy_list.h"
#include "./Logger/logger.h"
#include "./synchro_list/synchro_list.h"
#include "./stat/manip_fichier.h"
#include "./stat/stat.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
    pid_t pid_client = -1, pid_serveur = -1;
    pid_serveur = fork();

    printf("Lancement recherche serveur\n");
    if(pid_serveur == 0 )
    {
        execl("./test_serveur/serveur.c", "./test_serveur/serveur.c", NULL);
    }
    else //main
    {
        pid_client = fork();

        if(pid_client == 0)
        {
            execl("./test_serveur/client.c","./test_serveur/client.c",NULL);
        }
        else //main
        {
            for(int i =0 ; i<2; i++)
                wait(NULL);
            
            printf("Test Serveur terminé\n");

            printf("Appel module statistiques \n");

            statistique();

            printf("Module statistiques terminé\n");

            printf("Appel module copie liste \n");

            copy_list();

            printf("Module copie liste terminé\n");
            
        }
    }
    return 0;
}