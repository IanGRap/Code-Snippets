// Ian Rapoport
// irapopor
// CS101
// 8 March 2017
// Graph ADT class for pa5
// Graph.c

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

void addToList(List L, int i);
int visit(Graph G, int u, List S, int time);

// struct
// private GraphObj type
typedef struct GraphObj{
  List* neighbors;
  int* colors;
  int* parents;
  int* discovers;
  int* finishes;
  int order;
  int size;
} GraphObj;

// Constructor
Graph newGraph(int n){
  if(n == NULL){
    printf("Graph Error: newGraph() called with NULL argument");
    exit(1);
  }
  Graph G = malloc(sizeof(GraphObj));
  G->neighbors = calloc(sizeof(List), n+1);
  G->colors = calloc(sizeof(int), n+1);
  G->parents = calloc(sizeof(int), n+1);
  G->discovers = calloc(sizeof(int), n+1);
  G->finishes = calloc(sizeof(int), n+1);
  G->order = n;
  G->size = 0;
  for(int i=1; i<=n; i++){
    G->neighbors[i] = newList();
    G->colors[i] = 0;
    G->parents[i] = NIL;
    G->discovers[i] = INF;
    G->finishes[i] = INF;
  }
  return G;
}

// Destructors
void freeGraph(Graph* pG){
  if(*pG != NULL && pG != NULL){
    for(int i=1; i<=getOrder(*pG); i++){
      freeList(&(*pG)->neighbors[i]);
    }
    free((*pG)->neighbors);
    free((*pG)->colors);
    free((*pG)->parents);
    free((*pG)->discovers);
    free((*pG)->finishes);
    free(*pG);
    *pG = NULL;
  }
}

// Access functions
int getOrder(Graph G){
  if(G == NULL){
    printf("Graph Error: getOrder() called with NULL argument");
    exit(1);
  }  
  return G->order;
}

int getSize(Graph G){
  if(G == NULL){
    printf("Graph Error: getSize() called with NULL argument");
    exit(1);
  }  
  return G->size;
}

int getParent(Graph G, int u){
  if(G == NULL || u == NULL){
    printf("Graph Error: getParent() called with NULL argument");
    exit(1);
  }  
  if(u<1 || u>getOrder(G)){
    printf("Graph Error: getParent() called with invalid argument\n");
    exit(1);
  }
  return G->parents[u];
}

int getDiscover(Graph G, int u){
  if(G == NULL || u == NULL){
    printf("Graph Error: getDiscover() called with NULL argument");
    exit(1);
  }  
  if(u<1 || u>getOrder(G)){
    printf("Graph Error: getParent() called with invalid argument\n");
    exit(1);
  }
  return G->discovers[u];
}

int getFinish(Graph G, int u){
  if(G == NULL || u == NULL){
    printf("Graph Error: getFinish() called with NULL argument");
    exit(1);
  }  
  if(u<1 || u>getOrder(G)){
    printf("Graph Error: getFinish() called with invalid argument\n");
    exit(1);
  }
  return G->finishes[u];
}

// Manipulation procedures
void makeNull(Graph G){
  if(G == NULL){
    printf("Graph Error: makeNull() called with NULL argument");
    exit(1);
  }  
  for(int i=1; i<=getOrder(G); i++){
    clear(G->neighbors[i]);
    G->colors[i] = 0;
    G->parents[i] = NIL;
    G->discovers[i] = INF;
    G->finishes[i] = INF;
  }
  G->size = 0;
}

void addEdge(Graph G, int u, int v){
  if(G == NULL || u == NULL || v == NULL){
    printf("Graph Error: addEdgel() called with NULL argument");
    exit(1);
  }  
  if(u<1 || u>getOrder(G) || v<1 || v>getOrder(G)){
    printf("Graph error: addEdge() called with invalid argument: %d %d\n", u, v);
    exit(1);
  }
  addToList(G->neighbors[u], v);
  addToList(G->neighbors[v], u);
  G->size++;
}

void addArc(Graph G, int u, int v){
  if(G == NULL || u == NULL || v == NULL){
    printf("Graph Error: addArc() called with NULL argument");
    exit(1);
  }  
  if(u<1 || u>getOrder(G) || v<1 || v>getOrder(G)){
    printf("Graph Error: addEdge() called with invalid argument\n");
    exit(1);
  }
  addToList(G->neighbors[u], v);
  G->size++;
}

void DFS(Graph G, List S){
  if(G == NULL){
    printf("Graph Error: DFS() called with NULL argument");
    exit(1);
  }
  if(length(S) != getOrder(G)){
    printf("Graph Error: transpose() called with improper length list");
    exit(1);
  }  
  for(int i=1; i<=getOrder(G); i++){
    G->colors[i] = 0;
    G->parents[i] = NIL;
  }  
  int time = 0;
  moveFront(S);
  int l = length(S);
  for(int i=0; i<l; i++){
    if(G->colors[get(S)] == 0){
      time = visit(G, get(S), S, time);
    }   
    moveNext(S); 
  }
  for(int i=0; i<l; i++){
    deleteBack(S);
  }
}

int visit(Graph G, int u, List S, int time){
  G->discovers[u] = ++time;
  G->colors[u] = 1;
  List L = G->neighbors[u];
  moveFront(L);
  while(index(L) != -1){
    if(G->colors[get(L)] == 0){
      G->parents[get(L)] = u;
      time = visit(G, get(L), S, time);
    }
    moveNext(L);
  }
  G->colors[u] = 2;
  G->finishes[u] = ++time;
  prepend(S, u);
  return time;
}

// Other Operations
void printGraph(FILE* out, Graph G){
  if(out == NULL){
    printf("Graph Error: printGraph() called with NULL reference");
    exit(1);
  } else if(G == NULL){
    printf("Graph Error: printGraph() called with NULL reference");
    exit(1);
  }
  for(int i=1; i<=getOrder(G); i++){
    fprintf(out, "%d: ", i);
    printList(out, G->neighbors[i]);
    fprintf(out, "\n");
  }
}

Graph transpose(Graph G){
  if(G == NULL){
    printf("Graph Error: transpose() called with NULL argument");
    exit(1);
  }  
  Graph N = newGraph(getOrder(G));
  for(int i=1; i<=getOrder(N); i++){
    moveFront(G->neighbors[i]);
    while(index(G->neighbors[i]) != -1){
      addArc(N, get(G->neighbors[i]), i);
      moveNext(G->neighbors[i]);
    }
  }
  return N;
}

Graph copyGraph(Graph G){
  if(G == NULL){
    printf("Graph Error: copyGraph() called with NULL argument");
    exit(1);
  }   
  Graph N = newGraph(getOrder(G));
  for(int i=1; i<=getOrder(N); i++){
    moveFront(G->neighbors[i]);
    while(index(G->neighbors[i]) != -1){
      addArc(N, i, get(G->neighbors[i]));
      moveNext(G->neighbors[i]);
    }
  }
  return N;
}

void addToList(List L, int i){
  if(L == NULL || i == NULL){
    printf("Graph Error: addToList() called with NULL argument");
    exit(1);
  }   
  if(length(L) == 0){
    append(L, i);
  } else {
    moveFront(L);
    while(index(L) != -1){
      if(get(L) > i){
        insertBefore(L, i);
        break;
      } else {
        moveNext(L);
      }
    }
    if(index(L) == -1){
      append(L, i);
    }
  }
}
