#ifndef LOG_H
#define LOG_H

/* Log Struct Declaration */
typedef struct {
    struct {
        int turnCount;
        char player;
        int x;
        int y;
    } turn; 
    int gameCount;
} Log;

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "LinkedList.h"

/* FORWARD DECLARATIONS */
void printGame(void*);
void freeGame(void*);
void printSettings(Settings*);
void printLogs(Settings*, LinkedList*);

#endif

