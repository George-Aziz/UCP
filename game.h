#ifndef GAME_H
#define GAME_H

/* Settings Struct Declaration */
typedef struct {
   int m;
   int n;
   int k;
} Settings;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "userinterface.h" /* For boardDisplay method */
#include "logs.h" /* For game struct */
#include "LinkedList.h"

/* TRUE/FALSE & INPUTSIZE Definitions */
#define FALSE 0
#define TRUE !FALSE
#define INPUTSIZE 1024 /* Used for buffer sizes with input */

/* FORWARD DECLRATIONS */
void actualGame(Settings*, LinkedList*);
int inputTurn(char**, int, Settings*, Log*);
int determinePlayer(int);
char** createArray(Settings*);
void initialiseBoard(char**, Settings*);
void freeBoard(Settings*, char**);
int horizontalCheck(char**, Settings*, int, int );
int verticalCheck(char** , Settings*, int, int);
int fDiagonalCheck(char** , Settings*, int, int);
int aDiagonalCheck(char** , Settings*, int, int);
int winCheck(char** , Settings* , int , int);
void changeSettings(Settings*);

#endif
