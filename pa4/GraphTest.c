/**************************************************************
 * James Michael Vrionis
 * JVrionis
 * 3-2-17
 * Programming Assingment 4
 * 
 * GraphTest.c: A test file for Graph ADT.
 *  
 *************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    int i, s, max, min, d, n=35;
    List  C = newList(); /* central vertices */
    List  P = newList(); /* peripheral vertices */
    List  E = newList(); /* eccentricities */
    Graph G = NULL;

    /* Build graph G */
    G = newGraph(n);
    for(i=1; i<n; i++){
       if( i%7!=0 ) addEdge(G, i, i+1);
       if( i<=28  ) addEdge(G, i, i+7);
    }
    addEdge(G, 9, 31);
    addEdge(G, 17, 13);
    addEdge(G, 14, 33);

    /* Print adjacency list representation of G */
    printGraph(stdout, G);

    /* Calculate the eccentricity of each vertex */
    for(s=1; s<=n; s++){
        BFS(G, s);
        max = getDist(G, 1);
        for(i=2; i<=n; i++){
            d = getDist(G, i);
            max = ( max<d ? d : max );
        }
        append(E, max);
    }

   /* Determine the Radius and Diameter of G, as well as the Central and 
      Peripheral vertices. */
    append(C, 1);
    append(P, 1);
    min = max = front(E);
    moveFront(E);
    moveNext(E);
    for(i=2; i<=n; i++){
        d = get(E);
        if( d==min ){
            append(C, i);
        }else if( d<min ){
            min = d;
            clear(C);
            append(C, i);
        }
        if( d==max ){
            append(P, i);
        }else if( d>max ){
            max = d;
            clear(P);
            append(P, i);
        }
        moveNext(E);
    }

    /* Results */
    printf("\n----------------------------------------------\n");
    printf("\n");
    printf("Radius = %d\n", min);
    printf("Central vert%s: ", length(C)==1?"ex":"ices");
    printList(stdout, C);
    printf("\n");
    printf("Diameter = %d\n", max);
    printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
    printList(stdout, P);
    printf("\n----------------------------------------------\n");
    printf("\n");

    /* Free objects  */
    freeList(&C);
    freeList(&P);
    freeList(&E);
    freeGraph(&G);

    Graph S = newGraph(200);
    int j = 0;
    for(j = 1; j < 200; ++j) {
        if(j % 2 == 1)
            addEdge(TestA, j, 200 - j);
        else if(j % 3 == 1)
            addArc(TestA, j, 200 - j);
   }

    for(i = 1; i < 200; ++i) {
        BFS(TestA, i);
        for(j = 1; j < 200; ++j) {
            int d = getDist(TestA, j);
            if(d != INF)
                printf("Dist %d-%d: %d\n", i, j, d);
        }
    }

    BFS(TestA, 10);
    List N = newList();
    getPath(N, TestA, 190);
    printf("Path from 10 to 190: ");
    printList(stdout, N);
    printf("\n");
    
    BFS(TestA, 101);
    List Q = newList();
    getPath(Q, TestA, 99);
    printf("Path from 101 to 99: ");
    printList(stdout, Q);
    printf("\n");
  
    freeList(&N);
    freeList(&Q);
   
    BFS(TestA, 10);
    BFS(TestA, 101);
    List TestB = newList();
    getPath(TestB, TestA, 99);
    printf("Path from 101 to 99 again: ");
    printList(stdout, TestB);
    printf("\n");

   
    freeList(&TestB);
    freeGraph(&TestA);
    return(0);
}
