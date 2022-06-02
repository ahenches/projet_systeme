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

FILE* ouvrir_fichier(char* path, char* mode);
int compareDeuxFichiers(char *file1, char *file2);
int nombreLignes(char *path);
void appendValueFichier(char *file, int value);
void appendStrFichier(char *file, char* value);
void appendTermlineFichier(char *file);
