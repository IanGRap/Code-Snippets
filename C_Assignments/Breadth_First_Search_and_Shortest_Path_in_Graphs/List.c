// Ian Rapoport
// irapopor
// CS101
// 25 February 2017
// List ADT written in C for pa4
// List.c

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// Private NodeObj type
typedef struct NodeObj{
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int i;
} ListObj;

Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  return(N);
}

List newList(void){
  List L = malloc(sizeof(ListObj));
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->length = 0;
  L->i = -1;
  return(L);
}

void freeNode(Node* pN){
  if(pN != NULL && *pN != NULL){
    free(*pN);
    *pN = NULL;
  }
}

void freeList(List* pL){
  if(pL != NULL && *pL != NULL){
    clear(*pL);
    free(*pL);
    *pL = NULL;
  }
}

int length(List L){
  if(L == NULL){
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return(L->length);
}

int index(List L){
  if(L == NULL){
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }
  return(L->i);
}

int front(List L){
  if(L == NULL){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  } else if (length(L) == 0){
    printf("List Error: calling front() on length 0 List\n");
    exit(1);
  }
  return(L->front->data);
}

int back(List L){
  if(L == NULL){
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  } else if (length(L) == 0){
    printf("List Error: calling back() on length 0 List\n");
    exit(1);
  }
  return(L->back->data);
}

int get(List L){
  if(L == NULL){
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  } else if (length(L) <= 0){
    printf("List Error: calling get() on length 0 List\n");
    exit(1);
  } else if (index(L) <= -1){
    printf("List Error: calling get() on undefined cursor\n");
    exit(1);
  }
  return(L->cursor->data);
}

int equals(List A, List B){
  if(A == NULL || B == NULL){
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }
  if(length(A) != length(B)){
    return(0);
  } else {
    Node N = A->front;
    Node M = B->front;
    int equal = 1;
    for(int i=0; i<length(A); i++){
      if(N->data != M->data){
        equal = 0;
      }
      N = N->next;
      M = M->next;
    }
    N = NULL;
    M = NULL;
    freeNode(&N);
    freeNode(&M);
    return(equal);
  }
}

void clear(List L){
  if(L == NULL){
    printf("List Error: calling clear() on NULL List reference\n");
    exit(1);
  }
  while(length(L)>0){
    deleteFront(L);
  }
}

void moveFront(List L){
  if(L == NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(1);
  } else if(length(L) > 0){
    L->cursor = L->front;
    L->i = 0;
  }
}

void moveBack(List L){
  if(L == NULL){
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  } else if(length(L) > 0){
    L->cursor = L->back;
    L->i = length(L) - 1;
  }
}

void movePrev(List L){
  if(L == NULL){
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  } else if((L->cursor) != NULL){
    L->i--;
    if(L->i < 0){
      L->cursor = NULL;
    } else {
      L->cursor = L->cursor->prev;
    }
  }
}

void moveNext(List L){
  if(L == NULL){
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  } else if((L->cursor) != NULL){
    L->i++;
    if(L->i >= length(L)){
      L->cursor = NULL;
      L->i = -1;
    } else {
      L->cursor = L->cursor->next;
    }
  }
}

void prepend(List L, int data){
  if(L == NULL){
    printf("List Error: calling prepend() on NULL List refernce\n");
    exit(1);
  }  
  Node N = newNode(data);
  if(length(L) == 0){
    L->front = N;
    L->back = N;
  } else {
    N->next = L->front;
    L->front->prev = N;
    L->front = N;
  }
  L->length++;
  N = NULL;
  freeNode(&N);
  if(L->cursor != NULL){
    L->i++;
  }
}

void append(List L, int data){
  if(L == NULL){
    printf("List Error: calling append() on NULL List refernce\n");
    exit(1);
  }  
  Node N = newNode(data);
  if(length(L) == 0){
    L->front = N;
    L->back = N;
  } else {
    N->prev = L->back;
    L->back->next = N;
    L->back = N;
  }
  L->length++;
  N = NULL;
  freeNode(&N);
}

void insertBefore(List L, int data){
  if(L == NULL){
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  } else if (index(L) == -1){
    printf("List Error: calling insertBefore() on unidentified cursor\n");
    exit(1);
  } else if (length(L) <= 0){
    printf("List Error: calling insertBefore() on length 0 List\n");
    exit(1);
  }
  if(L->i == 0){
    prepend(L, data);
  } else {
    Node N = newNode(data);
    Node M = L->cursor->prev;
    N->prev = M;
    M->next = N;
    N->next = L->cursor;
    L->cursor->prev = N;
    L->i++;
    L->length++;
    N = NULL;
    freeNode(&N);
    M = NULL;
    freeNode(&M);
  }
}

void insertAfter(List L, int data){
  if(L == NULL){
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  } else if (index(L) == -1){
    printf("List Error: calling insertAfter() on unidentified cursor\n");
    exit(1);
  } else if (length(L) <= 0){
    printf("List Error: calling insertAfter() on length 0 List\n");
    exit(1);
  }
  if(L->i == 0){
    append(L, data);
  } else {
    Node N = newNode(data);
    Node M = L->cursor->next;
    N->next = M;
    M->prev = N;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length++;
    N = NULL;
    freeNode(&N);
    M = NULL;
    freeNode(&M);
  }
}

void deleteFront(List L){
  if(L == NULL){
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  } else if(length(L) > 0){
    if(index(L) == 0){
      L->cursor = NULL;
      L->i = -1;
    } else if(index(L) != -1){
      L->i--;
    }
    if(length(L) == 1){
      Node N=L->front;
      L->i = -1;
      L->length = 0;
      L->front = NULL;
      L->back = NULL;
      freeNode(&N);
      N = NULL;
    } else {
      Node N = L->front;
      L->front = L->front->next;
      L->front->prev = NULL;
      L->length--;
      freeNode(&N);
      N = NULL;
    }
  }
}

void deleteBack(List L){
  if(L == NULL){
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  } else if(length(L) > 0){
    if(index(L) == length(L)-1){
      L->cursor = L->cursor->prev;
      L->i--;
    }
    if(length(L) == 1){
      clear(L);
    } else {
      Node N = L->back;
      L->back = L->back->prev;
      L->back->next = NULL;
      L->length--;
      freeNode(&N);
      N = NULL;
    }
  }
}

void delete(List L){
  if(L == NULL){
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  }
  if(length(L) > 0 && L->i > -1){
    Node N;
    if(L->cursor->prev != NULL){
      N = L->cursor->prev;
      N->next = L->cursor->next;
    }
    if(L->cursor->next != NULL){
      N = L->cursor->next;
      N->prev = L->cursor->prev;
    }
    L->length--;
    freeNode(&L->cursor);
    L->cursor = NULL;
    L->i = -1;
  }
}

void printList(FILE* out, List L){
  if(L == NULL){
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  } else if (out == NULL){
    printf("List Error: calling printList() on NULL FILE reference\n");
    exit(1);
  }
  Node N = L->front;
  for(int i=0; i<length(L); i++){
    fprintf(out, "%d",  N->data);
    if(i != length(L)-1){
      fprintf(out, " ");
    } 
    N = N->next;
  }
  //fprintf(out, "\n");
  N = NULL;
  freeNode(&N);
}

List copyList(List L){
  if(L == NULL){
    printf("List Error: calling copy() on NULL List reference\n");
    exit(1);
  }  
  List R = newList();
  Node N = L->front;
  for(int i=0; i<length(L); i++){
    append(R, N->data);
    N = N->next;
  }
  N = NULL;
  freeNode(&N);
  return(R);
}

List concat(List L, List R){
  if(L == NULL || R == NULL){
    printf("List Error: calling concat() on NULL List reference\n");
    exit(1);
  }  
  List Q = copyList(L);
  Node N = R->front;
  for(int i=0; i<length(R); i++){
    append(Q, N->data);
    N = N->next;
  }
  N = NULL;
  freeNode(&N);
  return(Q);
}
