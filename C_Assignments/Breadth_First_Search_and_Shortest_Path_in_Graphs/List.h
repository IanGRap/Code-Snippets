// Ian Rapoport
// irapopor
// CS101
// 25 February 2017
// Header file for List ADT written in c for pa4
// List.h

#include<stdio.h>

typedef struct ListObj* List;

// Constructor
List newList(void);
// Destructor
void freeList(List* pL);

//Acess functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);

// Manipulation procedures
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations
void printList(FILE* out, List L);
List copyList(List L);
List concatList(List A, List B);
