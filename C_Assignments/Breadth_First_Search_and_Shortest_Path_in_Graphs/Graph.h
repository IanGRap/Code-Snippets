// Ian Rapoport
// irapopor
// CS101
// 25 February 2017
// Header class for Graph ADT for pa4
// Graph.h

#include "List.h"
#include<stdio.h>
#define INF -1
#define NIL 0

typedef struct GraphObj* Graph;

// Constructor
Graph newGraph(int n);

// Destructors
void freeGraph(Graph* pG);

// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation procedures
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other Operations
void printGraph(FILE* out, Graph G);
