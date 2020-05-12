/* The purpose of this file is be responsible for any of the tictactoe game's functionality */
#include "game.h"

/*********************************************************************************************
* FUNCTION: actualGame
* IMPORT: Settings struct pointer and LinkedList struct pointer
* EXPORT: LinkedList with log struct in it
* RETURN: none
* ASSERTION: Method that combines and uses all game functions in order for the game to be run
**********************************************************************************************/
void actualGame(Settings* settings, LinkedList* list)
{
    static int gameCount = 1; /* GameCount for logfiles */
    int turnCounter, winner, row, col; 
    char** boardArray;
    row = settings->n;
    col = settings->m;
    boardArray = NULL;
    winner = FALSE;
    turnCounter = 1; /* Counter for to determine which player (PlayerX = Odd) */

    /* boardArray gets created with the current imported settings */
    boardArray = createArray(settings);
    initialiseBoard(boardArray, settings);

    do
    { 
        /* Creates a new Log struct for everytime a new turn happens for each game */
        Log* log = (Log*)malloc(sizeof(Log)); 

        boardDisplay(boardArray, settings); 

        log->gameCount = gameCount; /* GameCount gets inserted for each log */
        log->turn.turnCount = turnCounter; /* Current turn gets inputted  */

        /* The user inputs their turn and returns an int value to indicate if winner has been found */
        winner = inputTurn(boardArray, turnCounter, settings, log);

        insertLast(list, log); /* After each succesful turn, the game structure will be inputted for logs*/
        turnCounter++;
    } 
    while(turnCounter != ((row * col) + 1) && winner == FALSE);
    gameCount++; /* After game is over, ready for next game if it begins with game 2,3,4... */
    
    if (turnCounter == ((row* col) + 1) && winner == FALSE) /* If the board is full with no winner */
    { 
        boardDisplay(boardArray, settings); /* The board will be displayed to show the final board */
        printf("\nThe game has ended on a draw!\n"); 
    }
    /* After every game, the board gets freed to prevent any mem leaks */
    freeBoard(settings, boardArray);
}

/*********************************************************************************************
* FUNCTION: createArray
* IMPORT: Settings struct pointer
* EXPORT: none
* RETURN: 2D Character Array
* ASSERTION: Function that creates the boardArray in order for player inputs to go through
**********************************************************************************************/
char** createArray(Settings* settings)
{
    /* N is rows and M is columns */
    int i, row, col;
    char** boardArray = NULL;
    row = settings->n;
    col = settings->m;

    boardArray = malloc(row * sizeof(char*)); /* Creates the rows for the array */
    for (i = 0; i < row; i++) 
    {
        boardArray[i] = malloc(col * sizeof(char)); /* Creates columns for the array */
    }

    return boardArray;
}

/*********************************************************************************************
* FUNCTION: initialiseBoard
* IMPORT: 2D Char Array and Pointer to settings struct
* EXPORT: 2D Character array filled with spaces ' '
* RETURN: none
* ASSERTION: Function to make the whole board filled with empty spaces
**********************************************************************************************/
void initialiseBoard(char** boardArray, Settings* settings)
{
    int i,j, row, col;
    row = settings->n;
    col = settings->m;

    for (i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            boardArray[i][j] = ' '; /* Filles with spaces as default for the whole board */
        }
    }
}

/*********************************************************************************************
* FUNCTION: freeBoard
* IMPORT: 2D Char Array and Pointer to settings struct
* EXPORT: none
* RETURN: frees the board array
* ASSERTION: Function that frees the boardArray
**********************************************************************************************/
void freeBoard(Settings* settings, char** boardArray)
{
    int i, row;
    row = settings->n;

    for (i = 0; i < row; i++) /* Freeing the rows for the 2D Array */
    {
        free(boardArray[i]); 
    }
    free(boardArray); /* Frees the columns for the 2D Array */
}

/******************************************************************************************************
* FUNCTION: inputTurn
* IMPORT: 2D Char Board Array, Int turnCounter, Settings struct pointer and Log Struct pointer
* EXPORT: Player Symbol, Player Location into Log Struct pointer AND fill boardArray with player symbol
* RETURN: Integer indicating if a winner has been found or not
* ASSERTION: Function to get player's move
*******************************************************************************************************/
int inputTurn(char** boardArray, int turnCounter, Settings* settings, Log* log)
{
    int x, y, player, winner, success, row, col, reader;
    char yStr[INPUTSIZE];
    char* endPtr; /* For error checking with Strtol */
    char playerSymbol = '\0'; /* Symbol for player */
    winner = FALSE; /* No winner found by default */
    success = FALSE; /* By default an input is invalid */
    /* Out of bound checking with row & col */
    row = settings->n;
    col = settings->m;
    
    player = determinePlayer(turnCounter);

    if (player == 1)
    { 
        playerSymbol = 'X';
    }
    else
    {
        playerSymbol = 'O';
    }

    do
    {
        printf("Please enter location for player %c: ", playerSymbol);
        reader = scanf("%d,%s", &x, yStr); /* Takes everything till a , */
        y = strtol(yStr, &endPtr, 10);

        if (*endPtr != '\0' || reader != 2)
        {
            scanf("%*[^\n]"); /* Clears the buffer to prevent infinite loop */
            printf("\nInvalid move, please follow (X,Y) formatting!\n\n"); 
        }
        else
        {
            if (x >= col || y >= row) /* Ensures no out of bounds input are allowed */
            {
                printf("\nInvalid move, try again!\n");
            }
            else
            {
                if(boardArray[y][x] != ' ') /* If the spot is taken */
                {
                    printf("\nInvalid move, try again!\n");
                }
                else
                {
                    boardArray[y][x] = playerSymbol;

                    log->turn.x = x;
                    log->turn.y = y;
                    log->turn.player = playerSymbol;

                    winner = winCheck(boardArray, settings, x, y);

                    if (winner == TRUE)
                    {
                        boardDisplay(boardArray, settings); 
                        printf("\nWinner is Player %c!\n", playerSymbol);
                    }
                    success = TRUE;
                }
            }
        }
    } while (!success); /* Success only true when an input is compeltely finished */
    
    return winner;

}


/*********************************************************************************************
* FUNCTION: deteriminePlayer
* IMPORT: countTurn as integer
* EXPORT: none
* RETURN: Player Number as Integer
* ASSERTION: Determins which player is currently playing for X or O
**********************************************************************************************/
int determinePlayer(int countTurn)
{
    int player;
    if (countTurn % 2 == 0) /* PlayerO is always even */
    {
        player = 2;
    }
    else
    {
        player = 1; /* PlayerX is always Odd */
    }
    return player;
}

/*********************************************************************************************
* FUNCTION: horizontalCheck
* IMPORT: 2D Char boardArray, Settings struct pointer, x and y as integers
* EXPORT: none
* RETURN: foundWinner Integer to indicate if a winner has been found
* ASSERTION: Win check for a horizontal line (Row)
**********************************************************************************************/
int horizontalCheck(char** boardArray, Settings* settings, int x, int y)
{
    int i, count, foundWinner, col, k;
    char currPlayer;
    col = settings->m;
    k = settings->k;
    foundWinner = FALSE;

    currPlayer = boardArray[y][x]; /* Current player to get playerSymbol */
    
    count = 0;

    for (i = 0; i < col; i++) /* Goes to the end of the width/row */
    {
            if(boardArray[y][i] == currPlayer) /* Only checks one row to be more efficient*/
            {
                count++;
            }
            else /* Resets the count since it needs to be consecutive same symbols */
            {
                count = 0;
            }

            if (count == k) /* If the count is equal to k then player has won */
            {
                foundWinner = TRUE;
            }
    }
    return foundWinner;
} 

/*********************************************************************************************
* FUNCTION: verticalCheck
* IMPORT: 2D Char boardArray, Settings struct pointer, x and y as integers
* EXPORT: none
* RETURN: foundWinner Integer to indicate if a winner has been found
* ASSERTION: Win check for a vertical line (Column)
**********************************************************************************************/
int verticalCheck(char** boardArray, Settings* settings, int x, int y)
{
    int i, count, foundWinner, row, k;
    char currPlayer;
    row = settings->n;
    k = settings->k;
    foundWinner = FALSE;

    currPlayer = boardArray[y][x]; /* Current player to get playerSymbol */
    
    count = 0;

    for (i = 0; i < row; i++) /* Goes to the end of the height/column */
    {
            if(boardArray[i][x] == currPlayer)  /* Only checks one column to be more efficient */
            {
                count++;
            }
            else /* Resets the count since it needs to be consecutive same symbols */
            {
                count = 0;
            }

            if (count == k) /* If the count is equal to k then player has won */
            {
                foundWinner = TRUE;
            }
    }
    return foundWinner;
} 

/*********************************************************************************************
* FUNCTION: fDiagonalCheck
* IMPORT: 2D Char boardArray, Settings struct pointer, x and y as integers
* EXPORT: none
* RETURN: foundWinner Integer to indicate if a winner has been found
* ASSERTION: Win check for forward diagonal (Top Left to Bottom Right)
**********************************************************************************************/
int fDiagonalCheck(char** boardArray, Settings* settings, int x, int y)
{
    int count, colCheck, rowCheck, foundWinner, col, row, k;
    char currPlayer;
    col = settings->m;
    row = settings->n;
    k = settings->k;
    foundWinner = FALSE;

    currPlayer = boardArray[y][x];

    count = 0;
    colCheck = 0;
    rowCheck = 0;

    if (x >= y) /* If x is greater than or equal to y */ 
    {
        /* The starting column will be where the top part of the diagonal line meant to start */
        colCheck = x - y;  
    } 
    else /* If y is greater than x */ 
    {
        /* The starting row will drop to where the first row of the diagonal line starts from */
        rowCheck = y - x; 
    }

    do 
    {
        if (boardArray[rowCheck][colCheck] == currPlayer) 
        {
            count++;
        }
        else /* Resets the count since it needs to be consecutive same symbols */
        {
            count = 0; 
        }
        
        if (count == k) /* If the count is equal to k then player has won */
        {
            foundWinner = TRUE; 
        }

        /* Both column and row increment since its a diagonal check */
        colCheck++; 
        rowCheck++;
    } 
    while(colCheck < col && rowCheck < row); /* Ensures that neither of the checks are out of bounds */

    return foundWinner;
}

/*********************************************************************************************
* FUNCTION: aDiagonalCheck
* IMPORT: 2D Char boardArray, Settings struct pointer, x and y as integers
* EXPORT: none
* RETURN: foundWinner Integer to indicate if a winner has been found
* ASSERTION: Win check for anti diagonal (Top Right to Bottom Left)
**********************************************************************************************/
int aDiagonalCheck(char** boardArray, Settings* settings, int x, int y)
{
    int count, colCheck ,rowCheck, foundWinner, row, col, k, i;
    char currPlayer;
    col = settings->m;
    row = settings->n;
    k = settings->k;
    foundWinner = FALSE;

    currPlayer = boardArray[y][x];

    count = 0;
    colCheck = x;
    rowCheck = y;


    for(i = 0; i < col; i++) /* Loop that checks for starting point of anti diag */
    {
        /* If the co-ords are not on the top/right edges of the board */
        if (colCheck != col-1 && rowCheck != 0) 
        {
            rowCheck--; /* The row will decrease to the top */
            colCheck++; /* The col will increase to the right */
        }
    } 

    do 
    {
        if (boardArray[rowCheck][colCheck] == currPlayer) 
        {
            count++;
        }
        else /* Resets the count since it needs to be consecutive same symbols */
        {
            count = 0; 
        }
        
        if (count == k) /* If the count is equal to k then player has won */
        {
            foundWinner = TRUE; 
        }

        /* Checks anti diagonal by going from top right to bottom left  */
        colCheck--; 
        rowCheck++;
    } 
    /* Ensures that neither of the checks are out of bounds */
    while(colCheck < col && rowCheck < row && colCheck >= 0 && rowCheck >= 0); 

    return foundWinner;
} 

/*********************************************************************************************
* FUNCTION: aDiagonalCheck
* IMPORT: 2D Char boardArray, Settings struct pointer, x and y as integers
* EXPORT: none
* RETURN: foundWinner Integer to indicate if a winner has been found
* ASSERTION: A function that checks for the winner by checking for every single type of win
**********************************************************************************************/
int winCheck(char** boardArray, Settings* settings, int x, int y)
{
    /* Each type of win has its own check */
    int hWinner = FALSE; 
    int vWinner = FALSE; 
    int fDWinner = FALSE;
    int aDWinner = FALSE;
    int foundWinner = FALSE; /* The main check to return if a winner has been found */

    /* Each type of check will commence to check if there is a winner */
    hWinner = horizontalCheck(boardArray,settings,x,y);
    vWinner = verticalCheck(boardArray, settings, x,y);
    fDWinner = fDiagonalCheck(boardArray, settings, x, y);
    aDWinner = aDiagonalCheck(boardArray, settings, x, y);

    /* If any of the checks return true then a winner has been found */
    if (hWinner == TRUE || vWinner == TRUE || fDWinner == TRUE || aDWinner == TRUE)
    {
        foundWinner = TRUE;
    }

    return foundWinner; /* Gets returned to the inputTurn function */
}

/*************************************************************************************************************
* FUNCTION: changeSettings
* IMPORT: Settings struct pointer
* EXPORT: New game settings
* RETURN: none
* ASSERTION: A function for when the program in EDITOR mode to allow users to change settings during runtime
**************************************************************************************************************/
void changeSettings(Settings* settings)
{
    /* Variables used for user input and error checking */
    int m,n,k, mSuccess, nSuccess, kSuccess;
    char* endptr;
    char mStr[INPUTSIZE];
    char nStr[INPUTSIZE];
    char kStr[INPUTSIZE];
    /* Used for error checking */
    mSuccess = FALSE;
    nSuccess = FALSE;
    kSuccess = FALSE;

    do 
    {
        printf("Please input value for M: ");
        scanf("%s", mStr);
        m = strtol(mStr, &endptr, 10); /* Makes sure only an int has been taken with no decimals */

        if (*endptr != '\0') /* If the endptr is not \0, means that there is something extra other than an int */
        {
            printf("\nERROR: Please input an integer!\n");
        }
        else
        {
            if (m < 1 || m > 999) /* Makes sure the m value is in the specefied range */
            {
                printf("\nERROR: Input is less than 1 or larger than 999!\n");
            }
            else
            {
                mSuccess = TRUE;
            }
        }
        
    }
    while (!mSuccess);

    do 
    {
        printf("Please input value for N: ");
        scanf("%s", nStr);
        n = strtol(nStr, &endptr, 10); /* Makes sure only an int has been taken with no decimals */

        if (*endptr != '\0') /* If the endptr is not \0, means that there is something extra other than an int */
        {
            printf("\nERROR: Please input an integer!\n");
        }
        else
        {
            if (n < 1 || n > 999) /* Makes sure the n value is in the specefied range */
            {
                printf("\nERROR: Input is less than 1 or larger than 999!\n");
            }
            else
            {
                nSuccess = TRUE;
            }
        }
        
    }
    while (!nSuccess);
    
    do 
    {
        printf("Please input value for K: ");
        scanf("%s", kStr);
        k = strtol(kStr, &endptr, 10); /* Makes sure only an int has been taken with no decimals */

        if (*endptr != '\0') /* If the endptr is not \0, means that there is something extra other than an int */
        {
            printf("\nERROR: Please input an integer!\n");
        }
        else
        {
            if (k < 1 || k > 999) /* Makes sure the k value is in the specefied range */
            {
                printf("\nERROR: Input is less than 1 or larger than 999!\n");
            }
            else if (k > n && k > m) /* Additional check for K to make sure its not larger than N and M */
            {
                printf("\nERROR: K must be in bounds of the board!\n");
            }
            else
            {
                kSuccess = TRUE;
            }
        }
    }
    while (!kSuccess);

    /* After all settings succesfully changed and validated settings for the game will change */
    settings->m = m;
    settings->n = n;
    settings->k = k;
}
