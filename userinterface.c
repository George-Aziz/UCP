/* The purpose of this file is to provide a main menu, display settings and display the board to the user */
#include "userinterface.h"

/**************************************************************************************
* SUBMODULE: mainMenu
* IMPORT: Settings and LinkedList pointers struct
* EXPORT: none
* ASSERTION: The first output the user sees and is able to go into parts of the program
***************************************************************************************/
void mainMenu(Settings* settings, LinkedList* list)
{
    int option; /* Option for the user to select from the main menu */
    int done = FALSE; /* when exit option gets selected, this will become true and end the program */
    char* endptr; /* endptr for strtol to see if there is any invalid values  */
    char str[INPUTSIZE]; /* input string */

    do
    {
        /* Main Output prompt to the user */
        printf("\n------=========MAIN MENU=========------\n");
        printf("1: Start a new game\n");
        printf("2: View the settings of the current game\n");
        printf("3: View the current logs\n");
        #if defined(SECRET) && defined(EDITOR)
        printf("4: Change game settings\n");
        printf("5: Exit the application\n");
        #elif SECRET
        printf("4: Exit the application \n");
        #elif EDITOR
        printf("4: Save logs to file\n");
        printf("5: Change game settings\n");
        printf("6: Exit the application \n");
        #else
        printf("4: Save logs to file\n");
        printf("5: Exit the application\n");
        #endif
        printf("=======================================\n");

        printf("\nPlease input option: ");
        scanf("%s", str);
        option = strtol(str, &endptr, 10);
        /* If anything other than \0, then that means there are invalid values */
        if (*endptr != '\0')
        {
            printf("\nERROR: Please select one of the options listed above!\n");
        }
        else 
        {
            switch(option)
            {
                case 1: /* Play the tic tac toe game */
                    actualGame(settings, list);
                break;
                case 2: /* Display game settings that is currently being used */
                    displaySettings(settings);
                break;
                case 3: /* Print the logs to the user */
                    printLogs(settings, list);
                break;
                #if defined(SECRET) && defined(EDITOR)
                case 4:
                    changeSettings(settings);
                break;
                case 5:
                    printf("You have selected to exit. Good Bye\n");
                    done = TRUE; 
                break;
                #elif SECRET
                case 4:
                    printf("You have selected to exit. Good Bye\n"); 
                    done = TRUE;
                break;
                #elif EDITOR
                case 4: 
                    writeFile(settings, list);
                break;
                case 5:
                    changeSettings(settings);
                break;
                case 6:
                    printf("You have selected to exit. Good Bye\n");
                    done = TRUE; 
                break;
                #else
                case 4: /* Write the logs to a file */
                    writeFile(settings, list);
                break;
                case 5: /* Exit Selection wiht output prompt */
                    printf("You have selected to exit. Good Bye\n"); 
                    done = TRUE;
                break;
                #endif
                default:
                    printf("\nERROR: Please select one of the options listed above!\n");
                break;
            }
        }
    } 
    /* Validation to ensure that this menu keeps being outputted unless the options in the selected range has been chosen */ 
    while(!done);
    
}

/**************************************************************************************
* FUNCTION: displaySettings
* IMPORT: Pointer to settings structure
* EXPORT: none
* ASSERTION: Displays current game settings
***************************************************************************************/
void displaySettings(Settings* settings)
{
    printf("\n\n---=====Curent Game Settings=====---\n");
    printf("Columns (M): %d \n", settings->m);
    printf("Rows (N): %d \n", settings->n);
    printf("Tiles to win (K): %d \n", settings->k);
}

/**************************************************************************************
* FUNCTION: boardDisplay
* IMPORT: A 2D Board Array and Pointer to settings struct
* EXPORT: none
* ASSERTION: Function that displays the board for when plalying the Tic Tac Toe Game
***************************************************************************************/
void boardDisplay(char** boardArray, Settings* settings)
{
    int i, j, k, row, column;
    column = settings->m;
    row = settings->n;

    for (i = 0; i < column; i++)
    {
        printf("====");
    }
    printf("===");

    printf("\n");
    for (i = 0; i < row; i++) /* Traverse the the rows */
    {
        for (j = 0; j < column; j++) /* Traverse the columns */
        {
            if (j == 0) /* Only for the first columns */
            {
                printf("|| ");
                printf("%c", boardArray[i][j]);
                printf(" |");
            }
            else if (j == (column-1)) /* Only for the last column */
            {
                printf(" %c", boardArray[i][j]);
                printf(" ||");
            } 
            else /* Everything else in the middle */
            {
                printf(" %c", boardArray[i][j]);
                printf(" |");
            }
        }

        if (i != (row - 1)) /* Formatting for last border row is different to the other rows */
        {
            printf("\n");
            for (k = 0; k < column; k++)
            {
                printf("----");
            }
            printf("---\n"); 
        } 
    }
    printf("\n");
    for (i = 0; i < column; i++)
    {
        printf("====");
    }
    printf("===\n");
} 
