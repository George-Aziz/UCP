#MAKEFILE VARIABLES
CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi -std=c89 -g
OBJ = TicTacToe.o fileManager.o userinterface.o game.o logs.o LinkedList.o
EXEC = TicTacToe

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

#CONDITIONAL COMPILATIONS
ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

ifdef SECRET
CFLAGS += -D SECRET
SECRET : clean $(EXEC)
endif

#FILES IN MAKEFILES
TicTacToe.o : TicTacToe.c fileManager.h LinkedList.h userinterface.h
	$(CC) $(CFLAGS) TicTacToe.c -c 

fileManager.o : fileManager.c fileManager.h game.h 
	$(CC) $(CFLAGS) fileManager.c -c 

userinterface.o : userinterface.c userinterface.h game.h
	$(CC) $(CFLAGS) userinterface.c -c 

game.o : game.c game.h userinterface.h logs.h
	$(CC) $(CFLAGS) game.c -c 

logs.o : logs.c logs.h game.h LinkedList.h
	$(CC) $(CFLAGS) logs.c -c

LinkedList.o : LinkedList.c LinkedList.h logs.h
	$(CC) $(CFLAGS) LinkedList.c -c

clean: 
	rm -f $(EXEC) $(OBJ)