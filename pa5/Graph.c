/**************************************************************
 
 * 
 * Graph.c: Graph ADT used to perform Depth-First Search on 
 * Graphs stored within.
 *  
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/* DFS algorithm */
#define WHITE 0
#define GRAY 1
#define BLACK 2

/* private GraphObj type */
struct GraphObj {
   List *adj;
   int *color;
   int *parent;
   int *discover;
   int *finish;
   int order;
   int size;
};

/*
 * newGraph():
 * Returns a reference to a new empty Graph.
 * A graph with vertices no edges
 */
Graph newGraph(int n) {
   Graph G = malloc(sizeof(struct GraphObj));
   G->adj = calloc(n + 1, sizeof(List));
   G->color = calloc(n + 1, sizeof(int));
   G->parent = calloc(n + 1, sizeof(int));
   G->discover = calloc(n + 1, sizeof(int));
   G->finish = calloc(n + 1, sizeof(int));
   G->order = n;
   G->size = 0;
   int i = 0;
   while ( i< (n+1) ) {
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   /*for(int i = 0; i < (n + 1); ++i) {
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }*/

   return G;
}

/*
 * freeGraph():
 * Frees all heap memory associated with Graph pG, and sets *pG to NULL.
 */
void freeGraph(Graph *pG) {
   Graph old = *pG;
   /*for(int i = 0; i < (old->order + 1); ++i) {
      freeList(&(old->adj[i]));
   }*/
   int i = 0; 
   while( i < (old->order + 1) ) { 
      freeList(&(old->adj[i]));
   }
   free(old->adj);
   free(old->parent);
   free(old->discover);
   free(old->finish);
   free(old->color);
   free(*pG);
   *pG = NULL;
}

/*
 * getOrder():
 * Returns the order of the graph.
 */
int getOrder(Graph G) {
   return G->order;
}

/*
 * getSize():
 * Returns the size of the graph.
 */
int getSize(Graph G) {
   return G->size;
}

/*
 * getParent():
 * Pre: 1<=u<=getOrder(G)
 * Returns the parent of vertex u in the DFS tree
 * or NIL if DFS() has not yet been called.
 */
int getParent(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
     printf("Graph Error: calling getParent() with vertex out of bounds\n");
     exit(1); 
   }
   return G->parent[u];
}

/*
 * getDiscover():
 * Pre: 1<=u<=n=getOrder(G)
 * Returns time of discovery with respect to vertex u
 *
 */
int getDiscover(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
     printf("Graph Error: calling getDiscover() with vertex out of bounds\n");
     exit(1); 
   }
   return G->discover[u];
}

/*
 * getFinish():
 * Pre: 1<=u<=n=getOrder(G)
 * Returns finish time with respect to vertex u
 *
 */
int getFinish(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
     printf("Graph Error: calling getFinish() with vertex out of bounds\n");
     exit(1); 
   }
   return G->finish[u];
}

/*
 * addEdge():
 * Pre: 1<=u<=getOrder(G) &&  1<=v<=getOrder(G)
 * Inserts a new edge, conecting two vertices u to v
 * i.e. u is added to the adjacency
 * List of v and v to the adjacency List of u.
 */
void addEdge(Graph G, int u, int v) {
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
     printf("Graph Error: calling addEdge() with verticies out of bounds\n");
     exit(1); 
   }
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}

/*
 * addArc():
 * Pre: 1<=u<=getOrder(G)  && 1<=v<=getOrder(G)
 * Inserts a new directed edge from u to v i.e. v
 * is added to the adjacency List of u (NOT u
 * onto adj of v
 */
void addArc(Graph G, int u, int v) {
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
     printf("Graph Error: calling addArc() with verticies out of bounds\n");
     exit(1); 
   }
   List S = G->adj[u];
   moveFront(S);
   
   while(index(S) > -1 && v > get(S)) {
      moveNext(S);
   }
   if(index(S) == -1)
      append(S, v);
   else 
      insertBefore(S, v);
   G->size++;
}

/*
 * visit():
 * Helper Function for DFS()
 *
 */
void Visit(Graph G, List S, int u, int *time) {
   G->color[u] = GRAY;
   G->discover[u] = ++*time;
   moveFront(G->adj[u]);
   while(index(G->adj[u]) >= 0) {
      int v = get(G->adj[u]);
      if(G->color[v] == WHITE) {
         G->parent[v] = u;
         Visit(G, S, v, time);
      }
      moveNext(G->adj[u]);
   }
   G->color[u] = BLACK;
   G->finish[u] = ++*time;
   prepend(S, u);
}

/*
 * DFS():
 * Pre: length(S)==getOrder(G)
 * Runs DFS() algorithm on a Graph G
 */
void DFS(Graph G, List S) {
   if(length(S) != getOrder(G)) {
      printf("Graph Error: called DFS() without matching sizes\n");
      exit(1);
   }
   int i = 0; 
   while ( i <= getOrder(G) ){ 
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
      ++i;
   }

   /*for(int i = 1; i <= getOrder(G); ++i) {
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   } */
   int time = 0;
   moveFront(S);

   while(index(S) >= 0) {
      int u = get(S);
      if(G->color[u] == WHITE) {
         Visit(G, S, u, &time);   
      }
      moveNext(S);
   }

   int size = length(S)/2; 
   while (size > 0) {
      deleteBack(S);
      --size;
   }
   /*for(int size = length(S)/2; size > 0; --size) {
      deleteBack(S);
   }*/

}

/*
 * printGraph()
 * Prints the adjacency list representation of G to the file pointed
 * to by out.
 */
void printGraph(FILE *out, Graph G) {
   if(out == NULL || G == NULL) {
      printf("Graph Error: called printGraph() on a null reference\n");
      exit(1);
   }
   
   int iter = 1; 
   while (iter <= getOrder(G) ) { 
      fprintf(out, "%d: ", iter);
      printList(out, G->adj[iter]);
      fprintf(out, "\n");
   }

/*   for(int i = 1; i <= getOrder(G); ++i) {
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
   }
*/   

}

/*
 * copyGraph():
 * Returns a reference to a new graph which is a copy of G.
 */
Graph copyGraph(Graph G) {
   int i = 1;
   Graph C = newGraph(getOrder(G));
   ++i;
   while (i <= getOrder(G)) {
      moveFront(G->adj[i]);
      while(index(G->adj[i]) >= 0) {
         addArc(C, i, get(G->adj[i])); 
         moveNext(G->adj[i]);
      }
   }
/*   for(int i = 1; i <= getOrder(G); ++i) {
      moveFront(G->adj[i]);
      while(index(G->adj[i]) >= 0) {
         addArc(C, i, get(G->adj[i])); 
         moveNext(G->adj[i]);
      }
   }
*/
   return C;
}

/*
 * transpose():
 * Return a reference to a new graph obj containing
 * the opposite directions in which the original
 * object had, that is, the Transpose of G
 */
Graph transpose(Graph G) {
   Graph T = newGraph(getOrder(G));
   
   for(int i = 1; i <= getOrder(G); ++i) {
      moveFront(G->adj[i]);
      while(index(G->adj[i]) >= 0) {
         addArc(T, get(G->adj[i]), i);
         moveNext(G->adj[i]);  
      }
   }
   return T;
}
