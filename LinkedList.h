#ifndef LISTNODE_H
#define LISTNODE_H

/* LinkedListNode Struct Declaration */
typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
}LinkedListNode;

/* LinkedList Struct Declaration */
typedef struct 
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int size;
} LinkedList;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logs.h"

/* FORWARD DECLRATIONS */
LinkedList* createLinkedList ();
void insertStart(LinkedList*, void*);
void insertLast(LinkedList*, void*);
void* removeStart (LinkedList*);
void* removeLast (LinkedList*);

/* Function Pointer Methods */
typedef void (*DataType)(void*);
typedef void (*FreeType)(void*);

void printLinkedList ( LinkedList *, DataType);
void freeLinkedList(LinkedList*, FreeType);

#endif
