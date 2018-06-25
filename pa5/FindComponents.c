/**************************************************************
 * 
 * FindComponent.c : This file should:  
 * 1)Read the input file.
 * 2) Assemble a graph object G using newGraph() and addArc(). 
 * 3) Print the adjacency list representation of G to the 
 * output file.
 * 4) Run DFS on G and GT , processing the vertices in the 
 * second call by decreasing finish times from the first call. 
 * 5) Determine the strong components of G.
 * 6) Print the strong components of G to the output file in 
 * topologically sorted order    
 *
 *************************************************************/


/* #include "List.h" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

#define MAX_LEN 255


int main(int argc, char* argv[]){
   
    FILE *in, *out;
    char line[MAX_LEN];

    /* Check command line for correct number of arguments */
    if( argc != 3 ) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
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

    fgets(line, MAX_LEN, in);
    int size = 0;
    sscanf(line, "%d", &size);

    List S = newList();
    for(int x = 1; x <= size; ++x) {
        append(S, x);
    }

    Graph G = newGraph(size);
    while( fgets(line, MAX_LEN, in) != NULL)  {
        int a = 0;
        int b = 0;
        sscanf(line, "%d %d", &a, &b);
        if(a == 0 && b == 0) {
            break;
        }
        addArc(G, a, b);   
    }
    
    DFS(G,S);
    Graph T = transpose(G);
    int scc = 0;
    DFS(T, S);
    moveFront(S);
    while(index(S) >= 0) {
        if(getParent(T, get(S)) == NIL)
            scc++;
        moveNext(S);
    }
  
    List TestList[scc];
    int i = 0;
    while(i < scc ){
        TestList[i] = newList();
    }
    // for(int i = 0; i < scc; ++i) {
    //     TestList[i] = newList();
    // }
   
    moveFront(S);
    int l = scc;
    while(index(S) >= 0) {
        if(getParent(T, get(S)) == NIL)
            --l;
        if(l == scc) 
            break;
        append(TestList[l], get(S));
        moveNext(S);
    }

    fprintf(out, "Adjacency list = :\n");
    printGraph(out, G);
    fprintf(out, "\nG contains %d strongly connected components:", scc);
    for(int m = 0; m < scc; ++m) {
        fprintf(out, "\nComponent %d: ", (m + 1));
        printList(out, TestList[m]);
        freeList(&(TestList[m]));
    }
    fprintf(out, "\n");
    freeGraph(&G);   
    freeGraph(&T);
    freeList(&S);

    /* close files */
    fclose(in);
    fclose(out);
    return(0);


}
