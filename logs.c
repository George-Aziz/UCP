#include "logs.h"

/**************************************************************************************
* FUNCTION: printGame
* IMPORT: Void* which gets typecasted to Log Struct
* EXPORT: none
* RETURN: none
* ASSERTION: A function used to display the each game Log
***************************************************************************************/
void printGame(void *inData)
{
    Log* data;
    int gameCount, turnCount, x, y;
    char player;

    data = (Log*)inData;

    gameCount = data->gameCount;
    turnCount = data->turn.turnCount;
    player = data->turn.player;
    x = data->turn.x;
    y = data->turn.y;

    printf("GAME %d:\n", gameCount);
    printf("   Turn: %d\n",turnCount);
    printf("   Player: %c\n", player);
    printf("   Location: %d,%d\n\n", x,y);
}

/**************************************************************************************
* FUNCTION: freeGame
* IMPORT: Void* which gets typecasted to Log Struct
* EXPORT: none
* RETURN: none
* ASSERTION: A function used to free each game Log struct
***************************************************************************************/
void freeGame(void *inData)
{
    Log* data;

    data = (Log*)inData; /* Typecast the imported data to free it */

    free(data);
}

/**************************************************************************************
* FUNCTION: printSettings
* IMPORT: A pointer to settings struct
* EXPORT: none
* RETURN: none
* ASSERTION: Prints out the settings in Log format
***************************************************************************************/
void printSettings(Settings* settings)
{
    int m,n,k;
    m = settings->m;
    n = settings->n;
    k = settings->k;

    /* Prints settings in format of logs as specefied in assignment spec */
    printf("SETTINGS:\n");
    printf("   M: %d\n", m);
    printf("   N: %d\n", n);
    printf("   K: %d\n\n", k);
}

/**************************************************************************************
* FUNCTION: printLogs
* IMPORT: A pointer to settings struct and a pointer to LinkedList struct
* EXPORT: none
* RETURN: none
* ASSERTION: Prints out the the Log by calling printSettings and then printing the list
***************************************************************************************/
void printLogs(Settings* settings, LinkedList* list)
{
    printSettings(settings);
    printLinkedList(list, printGame);
}
