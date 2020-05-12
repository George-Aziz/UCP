/* This file is responsible for the functionalities related to a LinkedList */
/* This File has been taken from my UCP Practical 7 work */
/* Aziz, George. (2019). UCP Structs Prac P07. */
#include "LinkedList.h"

/**************************************************************************************
* FUNCTION: createLinkedList
* IMPORT: none
* EXPORT: none
*  LinkedList Pointer
* ASSERTION: A method that constructs a new linked list 
***************************************************************************************/
LinkedList* createLinkedList ()
{
    LinkedList* list;

    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/**************************************************************************************
* FUNCTION: insertStart
* IMPORT: LinkedList pointer and void* for data
* EXPORT: A linked list with a new head node
* RETURN: none
* ASSERTION: Inserts a new node at the start of the list
***************************************************************************************/
void insertStart(LinkedList* ll,void* inData)
{
    /* Creates new node */
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->next = NULL; /* There is only one node now so there isn't anything next */
    newNode->prev = NULL; /* There is only one node now so there isn't anything previous */
    newNode->data = inData;
    if (ll->head == NULL) /* If the linkedList is currently empty */
    {
        ll->head = newNode; /* The newNode will be the head */
        ll->tail = newNode; /* Since it is empty the tail will also be the new node */
    }
    else
    {
        newNode->next = ll->head; /* Reference to next node for the newNode is the current head */
        ll->head->prev = newNode; /* The previous head's previous reference needs to be changed to the newNode */
        ll->head = newNode; /* The new node is now the new head of the linked list  */
    }
    ll->size++; /* The size/counter of the linked list increases by 1 */
}


/**************************************************************************************
* FUNCTION: insertLasT
* IMPORT: LinkedList pointer and void* for data
* EXPORT: A linked list with a new tail node
* RETURN: none
* ASSERTION: Inserts a new node at the end of the list
***************************************************************************************/
void insertLast(LinkedList* ll, void* inData)
{
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->next = NULL; /* There is only one node now so there isn't anything next */
    newNode->prev = NULL; /* There is only one node now so there isn't anything previous */
    newNode->data = inData;
    if (ll->tail == NULL) /* If the linkedList is currently empty */
    {
        ll->head = newNode; /* The newNode will be the head */
        ll->tail = newNode; /* Since it is empty the tail will also be the new node */
    }
    else
    {
        newNode->prev = ll->tail; /* Reference to prev node for the newNode is the current tail */
        ll->tail->next = newNode; /* The previous tail is now the 2nd last node in the list after the newNode */
        ll->tail = newNode;
    }
    ll->size++; 
}

/**************************************************************************************
* FUNCTION: removeStart
* IMPORT: LinkedList pointer
* EXPORT: A linkedlist with one less node
* RETURN: none
* ASSERTION: Removes the current head node
***************************************************************************************/
void* removeStart (LinkedList* ll)
{
    LinkedListNode* delNode;
    void* returnNode = NULL;
    if (ll->size == 0)
    {
        printf("ERROR: Nothing in LinkedList to remove!");
        delNode = NULL;
    }
    else
    {
        delNode = ll->head; /* The deleted node will be the current head */
        returnNode = delNode->data;
        ll->head = delNode->next; /* The new head of list is the next one after current Head */
        ll->head->prev = NULL;
        if (delNode->next == NULL)
        {
            ll->head = NULL;
            ll->tail = NULL;
        }
    }
    ll->size--;

    free(delNode);
    return returnNode;
}

/**************************************************************************************
* FUNCTION: removeLast
* IMPORT: LinkedList pointer
* EXPORT: A linkedlist with one less node
* RETURN: none
* ASSERTION: Removes the current tail node
***************************************************************************************/
void* removeLast (LinkedList* ll)
{
    LinkedListNode* delNode;
    void* returnNode = NULL;
    if (ll->size == 0)
    {
        printf("ERROR: Nothing in LinkedList to remove!");
        delNode = NULL;
    }
    /* Else if statement if the linkedlist contains only one node */
    else
    {
        delNode = ll->tail; /* The deleted node will be the the current tail */
        returnNode = delNode->data;
        ll->tail = delNode->prev; /* The new tail of list is the previous one from the current Tail */
        ll->tail->next = NULL;
        if (delNode->prev == NULL)
        {
            ll->head = NULL;
            ll->tail = NULL;
        }
    }

    ll->size--;
    free(delNode);
    return returnNode;
}

/**************************************************************************************
* FUNCTION: printLinkedList
* IMPORT: LinkedList pointer and a function pointer for printing the data type
* EXPORT: none
* RETURN: none
* ASSERTION: prints LinkedList
***************************************************************************************/
void printLinkedList (LinkedList * ll, DataType func)
{
    LinkedListNode *node, *nextNode;
 
    node = ll->head;

    if (node == NULL)
    {
        printf("\nThere is nothing to display!\n\n");
    }
    else 
    {
        while(node != NULL) 
        {
            nextNode = node->next;
            (*func)(node->data);
            node = nextNode;
        }
    }
}

/**************************************************************************************
* FUNCTION: freeLinkedList
* IMPORT: LinkedList pointer and a function pointer for freeing the data type
* EXPORT: none
* RETURN: none
* ASSERTION: frees LinkedList
***************************************************************************************/
void freeLinkedList(LinkedList* ll, FreeType func) 
{
    LinkedListNode *node, *nextNode;

    node = ll->head;
    while(node != NULL) 
    {
        nextNode = node->next;
        (*func)(node->data); 
        free(node);
        node = NULL;
        node = nextNode;
    }
    free(ll);
    ll = NULL;
}
