#include "manip_fichier.h"

FILE* ouvrir_fichier(char* path, char* mode){
    FILE *fptr;

    // use appropriate location if you are using MacOS or Linux
    fptr = fopen(path,mode);

    if(fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }

    //printf("Enter num: ");
    //scanf("%d",&num);

    //fprintf(fptr,"%d",num);
    
    return fptr;
}

// a utiliser sur ancienne_liste.txt / liste.txt
int compareDeuxFichiers(char *file1, char *file2) {
    FILE *f1 = ouvrir_fichier(file1,"r");
    FILE *f2 = ouvrir_fichier(file2,"r");

    char lines1[50][250];
    char lines2[50][250];

    int i;

    i = 0;
    while (fscanf(f1, "%[^\n] ", lines1[i]) != EOF){
        i++;
    }
    int sizeListe1 = i;

    i = 0;
    while (fscanf(f2, "%[^\n] ", lines2[i]) != EOF){
        i++;
    }
    int sizeListe2 = i;

    int retranche = 0;
    for (int i = 0; i < sizeListe1; i++)
    {
        for (int j = 0; j < sizeListe2; j++)
        {

            if (strcmp(lines1[i], lines2[j]) == 0){
                retranche++;
                // printf("1 : %s \n", lines1[i]);
                // printf("2 : %s \n", lines2[j]);
            }
            else{
 
            }
        }
        
    }
    int res = sizeListe1 + sizeListe2 - 2 * retranche;
    // printf("res : %d\n", res);
    fclose(f1);
    fclose(f2);

    return res;
}

int nombreLignes(char *path){
    int cptLignes = 0;
    int c;
    FILE *fichier;
    fichier = ouvrir_fichier(path,"r");
    do{
        c = fgetc(fichier);
        if(c=='\n'){
            cptLignes++;
        }
    }while (c!=EOF);

    return cptLignes;
}

void appendValueFichier(char *file, int value) {
    FILE *f = ouvrir_fichier(file, "a");
    
    fprintf(f, "%d", value);

    fprintf(f,"%s", "\t");

    fclose(f);
}
void appendStrFichier(char *file, char* value) {
    FILE *f = ouvrir_fichier(file, "a");

    fprintf(f, "%s", value);

    fprintf(f,"%s", "\t");
    fclose(f);
}
void appendTermlineFichier(char *file) {
    FILE *f = ouvrir_fichier(file, "a");

    fprintf(f,"%d", time(NULL));
    
    fprintf(f,"%s", "\n");
    fclose(f);
}



