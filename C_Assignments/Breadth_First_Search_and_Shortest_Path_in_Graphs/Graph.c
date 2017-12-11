// Ian Rapoport
// irapopor
// CS101
// 25 February 2017
// Graph ADT class for pa4
// Graph.c

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

void addToList(List L, int i);

// struct
// private GraphObj type
typedef struct GraphObj{
  List* neighbors;
  int* colors;
  int* parents;
  int* distances;
  int order;
  int lastSource;
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
  G->distances = calloc(sizeof(int), n+1);
  G->order = n;
  G->size = 0;
  G->lastSource = NIL;
  for(int i=1; i<=n; i++){
    G->neighbors[i] = newList();
    G->colors[i] = 0;
    G->parents[i] = NIL;
    G->distances[i] = INF;
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
    free((*pG)->distances);
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

int getSource(Graph G){
  if(G == NULL){
    printf("Graph Error: getSource() called with NULL argument");
    exit(1);
  }  
  return G->lastSource;
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

int getDist(Graph G, int u){
  if(G == NULL || u == NULL){
    printf("Graph Error: getDist() called with NULL argument");
    exit(1);
  }   
  return G->distances[u];
}

void getPath(List L, Graph G, int u){
  if(L == NULL || G == NULL || u == NULL){
    printf("Graph Error: getPath() called with NULL argument");
    exit(1);
  }  
  if(getSource(G) == NIL){
    printf("Graph Error: Most recent source is value NIL");
    exit(1);
  }
  if(G->distances[u] == INF){
    append(L, NIL);
  } else {
    int i = u;
    int d = G->distances[u];
    for(int j=0; j<=d; j++){
      prepend(L, i);
      i = G->parents[i];
    }
  }
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
    G->distances[i] = INF;
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

void BFS(Graph G, int s){
  if(G == NULL || s == NULL){
    printf("Graph Error: BFS() called with NULL argument");
    exit(1);
  }   
  G->lastSource = s;
  List Queue = newList();
  for(int i=1; i<=getOrder(G); i++){
    G->colors[i] = 0;
    G->distances[i] = INF;
    G->parents[i] = NIL;
  }
  G->colors[s] = 1;
  G->distances[s] = 0;
  append(Queue, s);
  int u, v;
  while(length(Queue) != 0){;
    u = front(Queue);
    deleteFront(Queue);
    if(length(G->neighbors[u]) != 0){
      moveFront(G->neighbors[u]);      
      while(index(G->neighbors[u]) != -1){
        v = get(G->neighbors[u]);
        moveNext(G->neighbors[u]);
        if(G->colors[v] == 0){
          G->colors[v] = 1;
          G->distances[v] = G->distances[u] + 1;
          G->parents[v] = u;
          append(Queue, v);
        }
      }
    }
    G->colors[u] = 2;
  }
  freeList(&Queue);
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
