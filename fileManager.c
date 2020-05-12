/* The purpose of this file is to be responsible of reading/saving from/to a file */
#include "fileManager.h"

/*********************************************************************************************
* FUNCTION: readFile
* IMPORT: Settings struct pointer sourceFile which is file name
* EXPORT: Settings from file
* RETURN: error int to indicate if an error has occured to stop main program from continuing
* ASSERTION: A function that reads settings from a file
**********************************************************************************************/
int readFile(char* sourceFile, Settings* settings)
{
    FILE* file = NULL;
    int numElements, num, mCount, nCount, kCount, m,n,k;
    char type;
    int done = FALSE;
    int error = FALSE;
    type = '\0';

    /* Variables used for error checking */
    m = 0;
    n = 0;
    k = 0;
    /* Variables used for duplicate check */
    mCount = 0;
    nCount = 0;
    kCount = 0;

    file = fopen(sourceFile, "r"); /* Opens input stream for settings file */

    if (file == NULL) 
    { 
        perror("ERROR: Unable to open settings file!");
        error = TRUE;
    }
    else 
    {
       /* done becomes True only when numElements doesn't return 2 */ 
        while (!done) 
        {
            numElements = fscanf(file, "%c=%d\n", &type ,&num);
            type = upperCase(type); /* Makes all MNK into caps to only check for caps */
            if (numElements == 2) 
            {
                if (type == 'M')
                {
                    m = num; 
                    settings->m = m;
                    mCount++;
                }
                else if (type == 'N')
                {
                    n = num; 
                    settings->n = n;
                    nCount++; 
                }
                else if (type == 'K')
                {
                    k = num; 
                    settings->k = k;
                    kCount++; 
                } 
            }
            else 
            {
                done = TRUE; /* If numElement != 2 then the loop will end */
                if (numElements != EOF) 
                {
                    /* Fscanf also takes in EOF, so this prints only if a line is invalid in the actual file */
                    printf("ERROR: Invalid Line Format!\n");
                    error = TRUE;
                }
                else /* If the end of file has reached then all other error checking will proceed */
                {
                    /* If any of the counts are larger than 1 then there is a duplicate setting */
                    if((mCount > 1) || (nCount > 1) || (kCount > 1))
                    {
                        error = TRUE;
                        printf("ERROR: There are duplicate settings!\n");
                    }

                    /* If any of the counts are 0 then they haven't been added  */
                    if (mCount == 0 || nCount == 0 || kCount == 0)
                    {
                        error = TRUE;
                        printf("ERROR: One or more settings don't exist!\n");
                    }
                    else
                    {
                        /* If K is larger than rows and columns then it is off the board which is invalid */
                        if ((k > n) && (k > m))
                        {
                            error = TRUE; 
                            printf("ERROR: K is larger than board dimension!\n");
                        }
                        /* A limit to how large the values can go */
                        if (k > 999 || m > 999 || n > 999)
                        {
                            error = TRUE;
                            printf("ERROR: One or more settings have value larger than 999!\n");
                        }
                        /* No value can be negative or 0*/
                        if (k < 1 || m < 1 || n < 1)
                        {
                            error = TRUE;
                            printf("ERROR: One or more settings have values less than 1!\n");
                        }
                    }
                }
                /* Only closes the file if it has been opened */
                fclose(file); /* Makes sure the file is closed at the end */
            }
        }
    }

    return error; /* Error returned in order to end the program in the main succesfully */ 
}

/*********************************************************************************************
* FUNCTION: upperCase
* IMPORT: Character
* EXPORT: none
* RETURN: Character in upper case
* ASSERTION: Function that converts any character to upperCase
**********************************************************************************************/
/* Aziz, George. (2019). UCP Pointer Functions Prac P04. */
/* This function has been taken from partical Practical 4 and has been adjusted for characters rather than Strings  */
char upperCase(char character)
{
    if (character >= 'a' && character <= 'z') /* Ensures its within the alphabet */
    {
        character = character - 32; /* Makes the character upperCase */
    }
    return character; /* rerutns the new upper Case character */
}

/*********************************************************************************************
* FUNCTION: writeFile
* IMPORT: Settings struct pointer, list struct pointer
* EXPORT: none
* RETURN: none
* ASSERTION: Function to write logs to a file 
**********************************************************************************************/
/* Reference for using the time struct */
/* Techie Delight. 2019. "Print current date and time in C". : https://www.techiedelight.com/print-current-date-and-time-in-c/ */
void writeFile(Settings* settings, LinkedList* list)
{
    FILE *logFilePtr = NULL; 
    char fileName[INPUTSIZE];
    /* Log struct variables */
    LinkedListNode *node, *nextNode;
    int gameCount, turnCount, x, y, m,n,k;
    char player;
    Log* logStruct = NULL;

    /* Variables to store date and time components */
	int hours, minutes, day, month;
    time_t now;
    struct tm *local;
    
    /* Assigning the date/time for fileName */
    time(&now); 
    local = localtime(&now);
    hours = local->tm_hour;      	
    minutes = local->tm_min;     	 	
    day = local->tm_mday;        	
    month = local->tm_mon + 1;   	

    /* Settings varibales */
    m = settings->m;
    n = settings->n;
    k = settings->k;

    /* Creating the format for the fileName */
    sprintf(fileName, "MNK_%d-%d-%d_%d-%d_%d-%d.log", m, n, k, hours ,minutes, day, month); 	

    /* Opens a file to write */
    logFilePtr = fopen(fileName, "w"); 
    
    /* Settings get displayed at the top of the file */
    fprintf(logFilePtr, "SETTINGS:\n");
    fprintf(logFilePtr, "   M: %d\n",m);
    fprintf(logFilePtr, "   N: %d\n",n);
    fprintf(logFilePtr, "   K: %d\n\n",k);

    /* The first node to be printed is the head */
    node = list->head;
    while(node != NULL) 
    {
        nextNode = node->next;
        logStruct = (Log*)(node->data); /* Typecast the node to a game struct */
        /* Log struct variables */
        gameCount = logStruct->gameCount;
        turnCount = logStruct->turn.turnCount;
        player = logStruct->turn.player;
        x = logStruct->turn.x;
        y = logStruct->turn.y;

        /* Log/Turn formatting for file writing */
        fprintf(logFilePtr, "GAME %d:\n", gameCount);
        fprintf(logFilePtr, "   Turn: %d\n", turnCount);
        fprintf(logFilePtr, "   Player: %c\n", player);
        fprintf(logFilePtr, "   Location: %d,%d\n\n", x,y);

        node = nextNode; /* Assigns the nextNode to be printed */
    }

    fclose(logFilePtr);
}
