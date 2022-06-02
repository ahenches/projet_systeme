/*
 * Project myLogger
 * Author: Wissal Benharouga
 * Date: 29/05/2022
 * Purpose: Create log in a file at every call
*/

//Déclaration des dépendances
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Prototype
void writeTextFromBuffer(FILE*, char*);
void logSomething(char*);