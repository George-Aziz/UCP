#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "game.h"

/* False/True Definitions for later usage in file */
#define FALSE 0
#define TRUE !FALSE

/* FORWARD DECLARATIONS */
int readFile(char*, Settings*);
char upperCase(char);
void writeFile(Settings*, LinkedList*);

#endif
