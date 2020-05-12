#include <stdio.h>

#include "fileManager.h" /* To read file */
#include "userinterface.h" /* To get the main menu */
#include "LinkedList.h" /* To get the LinkedList struct */

/**************************************************************************************
* IMPORT: argc (Integer), argv (A String/ Char* Array)
* EXPORT: none
* RETURN: 0
* ASSERTION: Main function to start the program
***************************************************************************************/
int main(int argc, char* argv[]) 
{
    char* sourceFile = argv[1]; /* Whatever is after the program name is the sourceFile name  */
    int errorCheck;
    LinkedList* list;
    if(argc < 2) /* Ensures that the settings file is imported */
    {
        printf("Usage: %s <settingsFile> \n", sourceFile);
    }
    else 
    {
        /* Initialise struct and only use size of 1 since there will only be 1 instance of settings */
        Settings* settings = (Settings*)malloc(sizeof(Settings));
        errorCheck = readFile(sourceFile, settings);
    
        if (errorCheck == FALSE)
        {
            list = createLinkedList();

            mainMenu(settings, list);
            
            freeLinkedList(list, freeGame); 
        }
        free(settings);
    }
    return 0;
}
