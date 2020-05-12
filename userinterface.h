#ifndef UI_H
#define UI_H

#include <stdio.h>
#include "game.h"
#include "logs.h"
#include "LinkedList.h"
#include "fileManager.h"

/* INPUTSIZE Definition for input buffer size error checking */
#define INPUTSIZE 1024

/* FORWARD DECLARATIONS */
void mainMenu(Settings*, LinkedList*);
void displaySettings(Settings*);
void boardDisplay(char**, Settings*);

#endif
