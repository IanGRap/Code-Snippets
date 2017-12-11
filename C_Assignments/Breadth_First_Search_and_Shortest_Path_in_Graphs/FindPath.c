// Ian Rapoport
// irapopor
// CS101
// 25 February 2017
// Reads and outputs files for pa4 and prints Graph data (adapted from FileIO.c)
// FindPath.c

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int size, u, v, s, d;
   Graph G;
   List L;
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
   fscanf(in, "%d\n", &size);

   G = newGraph(size);

   // read in the values for the edges and verticies of the graph
   while(1){
     fscanf(in, "%d %d\n", &u, &v);
     if(u == 0 || v == 0){
       break;
     }     
     addEdge(G, u, v);
   }

   //fgets(line, MAX_LEN, in);
   printGraph(out, G);
   L = newList();
   
   while(1){
     fscanf(in, "%d %d\n", &s, &d);
     if(s == 0 || d == 0){
       break;
     }    
     fprintf(out, "\n");
     BFS(G, s);
     if(getDist(G, d) != INF){
       fprintf(out, "The distance from %d to %d is %d\n", s, d, getDist(G, d));
       getPath(L, G, d);
       fprintf(out, "A shortest %d-%d path is: ", s, d);
       printList(out, L);
       fprintf(out, "\n");
     } else {
       fprintf(out, "The distance from %d to %d is infinity\n", s, d);
       fprintf(out, "No %d-%d path exists\n", s, d);
     }
     //fprintf(out, "\n");
     clear(L);
   }

  // close files and free memory
  makeNull(G);
  freeGraph(&G);
  freeList(&L);
  fclose(in);
  fclose(out);

  return(0);
}
