// Ian Rapoport
// irapopor
// CS101
// 8 March 2017
// Reads and outputs files for pa5 and prints Graph and DFS data
// FindPath.c

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int order, u, v, components;
   Graph G;
   List S, C;
   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
     printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
     printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
     printf("Unable to open file %s for writing\n", argv[2]);
     exit(1);
   }

   // get the number of verticies
   fscanf(in, "%d\n", &order);

   G = newGraph(order);

   // read in the values for the edges and verticies of the graph
   while(1){
     fscanf(in, "%d %d\n", &u, &v);
     if(u == 0 || v == 0){
       break;
     }     
     addArc(G, u, v);
   }

   //fgets(line, MAX_LEN, in);
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out, "\n");

   S = newList();
   for(int i=1; i<=order; i++){
     append(S, i);
   }

   DFS(G, S);

   Graph T = transpose(G);
   DFS(T, S);

   moveBack(S);
   components = 0;
   while(index(S) != -1){
     if(getParent(T, get(S)) == NIL){
       components++;
     }
     movePrev(S);
   }

   fprintf(out, "G contains %d strongly connected components:\n", components);
   moveBack(S);
   C = newList();
   int i = 1;
   while(index(S) != -1){
     prepend(C, get(S));
     if(getParent(T, get(S)) == NIL){
       fprintf(out,"Component %d: ", i++);
       printList(out, C);
       fprintf(out, "\n");
       clear(C);
     }
     movePrev(S);
   }


  // close files and free memory
  makeNull(G);
  freeGraph(&G);
  makeNull(T);
  freeGraph(&T);
  clear(S);
  freeList(&S);
  clear(C);
  freeList(&C);
  fclose(in);
  fclose(out);

  return(0);
}
