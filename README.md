# Unix and C Programming Assignment Readme

Date last modified: 20/10/19

## Purpose: 
To create a dynamic size board tic tac toe game

## Files in project: 
- **TicTacToe.c** : file with the main
- **MakeFile** : for compiling
- **settings** : contains game settings
- **fileManager.c** : file reader/writer functions
- **game.c** : all game functionality 
- **LinkedList.c** : generic linked list data structure functions
- **Logs.c** : responsible for game logging format and log strurct
- **userinterface.c** : interface of program/game

## Test Files: 
N/A

## Functionality: 
Settings file contents: M = Columns, N = Rows, K = number of tiles in a row to win

Compiling modes:
- Default mode:`make`
- Secret mode: `make SECRET=1`
- Editor mode: `make EDITOR=1`
- Additionally, you can also compile with both modes as well by stating both modes = 1

To run after compile `./TicTacToe <settings_file>`


## TODO: 
N/A
