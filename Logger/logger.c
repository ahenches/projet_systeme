#include"logger.h"

//Fonctions
void writeTextFromBuffer ( FILE * file, char* message) // message: c'est le texte qu'on va écrire
{
    unsigned long length = strlen(message);  //taille du texte
    const int REGULARPACKAGE_SIZE = 128;    //taille max qu'on va tranférer à chaque fois
    unsigned long bytesWritten = 0;                   /* Bytes written so far in the buffer*/
    int bytesToWrite;                             /* Bytes to write to file */
    char *tmpBuffer;                              /* Temporary buffer: il va prendre la taille max */
    int counter = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // allocate tmpBuffer
    tmpBuffer = (char *) malloc ( REGULARPACKAGE_SIZE ); // on alloue la mémoire avec la taille maximum
    printf("%d lenght\n", length);
    fprintf(file, "-------- %02d/%02d/%d  %02d h %02d min %02d sec --------\n",  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    while ( bytesWritten < length )
    {
        printf("Blocs ecrits dans le fichier: %d\n", counter);
        if ( length - bytesWritten >= REGULARPACKAGE_SIZE )  /* not last frame */
        {
            bytesToWrite = REGULARPACKAGE_SIZE;
        }
        else                                                 /* last frame */
        {
            bytesToWrite = length - bytesWritten;
        }
        // copy original message <bytesToWrite> elements to tmpBuffer
        tmpBuffer = &message[bytesWritten];
        //printf("%s message", message[bytesWritten]);

        // write tmpBuffer to file

        fwrite ( tmpBuffer , 1 , bytesToWrite , file ); // on écrit le tmpbuffer de taille bytesToWrite dans file
        fputs("\n", file);

        // just upgrade the var
        bytesWritten += bytesToWrite; //update de position pour la prochaine boucle
        counter++;
    }
    fputs("------------------------------------------------\n", file);

}

void logSomething(char * message){

    //Déclaration des variables
    FILE *fichier;
    //getdate string name = date ... name = cancat "C:\\Users\\wissa\\CLionProjects\\myLogger\\log"+ name + ".txt"
    time_t t = time(NULL);
    char path[255];

    struct tm tm = *localtime(&t);
    sprintf(path,"./Logger/log_%d-%02d-%02d_%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour);

    //Debut
    fichier = fopen(path, "a");//Ouverture du fichier
    if(fichier == NULL){//test après fopen (NULL si fichier non ouvert)

        printf("\nATTENTION LE FICHIER N'EST PAS CRÉÉE\n");

    }else{

        printf("\nOUVERTURE FICHIER\n");
        //fprintf(fichier, "\nmessage");
        writeTextFromBuffer(fichier, message);
        if(fclose(fichier) == -1){//Fermeture du fichier

            printf("\nATTENTION ERREUR DE FERMETURE FICHIER\n");

        }else{

            printf("\nFERMETURE FICHIER AVEC SUCCÈS\n");

        }
    }
}
