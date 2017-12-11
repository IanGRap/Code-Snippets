// Ian Rapoport
// irapopor
// CS101
// 8 March 2017
// Header class for Graph ADT for pa5
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
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation procedures
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

// Other Operations
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
