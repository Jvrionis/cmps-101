/**************************************************************
 * James Michael Vrionis
 * JVrionis
 * 3-2-17
 * Programming Assingment 4
 * 
 * Graph.c: Graph ADT that represents a graph as an array of 
 * lists.
 *  
 *************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"


/* private GraphObj type */
typedef struct GraphObj {
    List* adj;
    char* color;
    int* parent;
    int* distance;
    int order;
    int size;
    int source;
} GraphObj;

/* private Graph type */
typedef struct GraphObj* Graph;

/*
 * newGraph():
 * Returns a reference to a new empty Graph.
 * A graph with vertices no edges
 */
Graph newGraph(int n) {
     Graph G = malloc(sizeof(GraphObj));
     G->adj = calloc(n+1, sizeof(List));
     G->color = calloc(n+1, sizeof(char));
     G->parent = calloc(n+1, sizeof(int));
     G->distance = calloc(n+1, sizeof(int));
     G->source = NIL;
     G->order = n;
     G->size = 0;
   
    for(int i = 1; i <= n; i++){
        G->adj[i] = newList();
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return G;
}

/*
 * freeGraph():
 * Frees all heap memory associated with Graph pG, and sets *pG to NULL.
 */
void freeGraph(Graph* pG) {
    if(pG != NULL && (*pG) != NULL) {
        for(int i = 1; i <= getOrder(*pG); i++) {
            freeList(&((*pG)->adj[i]));
        }
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*
 * getOrder():
 * Returns the order of the graph.
 */
int getOrder(Graph G) { 
    if(G == NULL) {
        printf("Graph Error(1): getOrder() called on NULL Graph.\n");
        exit(1);
    }
    return G->order;
}

/*
 * getSize():
 * Returns the size of the graph.
 */
int getSize(Graph G) {
    if(G == NULL) {
        printf("Graph Error(2): getSize() called on NULL Graph.\n");
        exit(1);
    }
    return G->size;
}

/*
 * getSource():
 * Returns the source vertex most recently used in function BFS(), or
 * NIL if BFS() has not yet been called.
 */
int getSource(Graph G) {
    if(G == NULL) {
        printf("Graph Error(3): getSource() called on NULL Graph.\n");
        exit(1);
    }
    return G->source;
}

/*
 * getParent():
 * Pre: 1<=u<=getOrder(G)
 * Returns the parent of vertex u in the BFS tree 
 * or NIL if BFS() has not yet been called.
 */
int getParent(Graph G, int u) {
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error(4): getParent() called on unknown vertex.\n");
        exit(1);
    }
    return G->parent[u];
}

/*
 * getDist():
 * Pre: 1<=u<=getOrder(G)
 * Returns the distance from the most recent BFS source to vertex u,
 * or INF if BFS() has not yet been called.
 */
int getDist(Graph G, int u) {
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error(5): getDist() called on unknown vertex.\n");
        exit(1);
    }
    return G->distance[u];
}

/*
 * getPath():
 * Pre: 1<=u<=getOrder(G) &&  getSource(G) != NIL
 * Appends the vertices of shortest path in G to  List L 
 * source to u, or appends to L the value NIL if no such path exists.
 */
void getPath(List L, Graph G, int u) {
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error(6): getPath() called on unknown vertex.\n");
        exit(1);
    }
    if(getSource(G) == NIL) {
        printf("Graph Error(7): getPath() called on undefined source.\n");
        exit(1);
    }   
    if( u == getSource(G) ) {
        append(L, u);
    } else if ( getParent(G, u) == NIL) {
        append(L, NIL);
    } else {
        prepend(L, u);
        int par = getParent(G, u);
        while( (par != getSource(G)) && (par != NIL) ) {
            prepend(L, par);
            par = getParent(G, par);
        }
        prepend(L, par);
    }
}

/*
 * makeNull()
 * Deletes all edges of G, restoring it to its original (no edge) 
 * state. 
 */
void makeNull(Graph G) {
    for(int i = 1; i <= getOrder(G); i++) {
        clear(G->adj[i]);
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->size = 0;
    G->source = NIL;
}

/*
 * addEdge():
 * Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
 *  Inserts a new edge joining u to v, i.e. u is added to the adjacency
 * List of v and v to the adjacency List of u.
 */
void addEdge(Graph G, int u, int v) {
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error(8): addEdge() called on unknown vertex.\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)) {
        printf("Graph Error(9): addEdge() called on unknown vertex.\n");
        exit(1);
    }
   
    int current = -1;

    moveTo(G->adj[u], 0);
    if(getIndex(G->adj[u]) != -1) {
        current = getElement(G->adj[u]);
    }
    while(current < v && getIndex(G->adj[u]) != -1) {
        moveNext(G->adj[u]);
        if(getIndex(G->adj[u]) != -1) {
            current = getElement(G->adj[u]);
        }
    }
    if(getIndex(G->adj[u]) !=  -1) {
        insertBefore(G->adj[u], v);
    }else {
        append(G->adj[u], v);
    }

    moveTo(G->adj[v], 0);
    if(getIndex(G->adj[v]) != -1) {
        current = getElement(G->adj[v]);
    }
    while(current < u && getIndex(G->adj[v]) != -1) {
        moveNext(G->adj[v]);
        if(getIndex(G->adj[v]) != -1){
            current = getElement(G->adj[v]);
        }
    }
    if(getIndex(G->adj[v]) !=  -1) {
        insertBefore(G->adj[v], u);
    }else {
        append(G->adj[v], u);
    }
    G->size++;
}

/*
 * addArc():
 * Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
 * Inserts a new directed edge from u to v, i.e. v is added to the 
 * adjacency List of u (but not u to the adjacency List of v).
 */
void addArc(Graph G, int u, int v) {
    if(u < 1 || u > getOrder(G)) {
        printf("Graph Error(10): addEdge() called on unknown vertex.\n");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)) {
        printf("Graph Error(11): addEdge() called on unknown vertex.\n");
        exit(1);
    }
    int current = -1;

    moveTo(G->adj[u], 0);
    if(getIndex(G->adj[u]) != -1) {
        current = getElement(G->adj[u]);
    }
    while(current < v && getIndex(G->adj[u]) != -1) {
        moveNext(G->adj[u]);
        if(getIndex(G->adj[u]) != -1) {
            current = getElement(G->adj[u]);
        }
    }
    if(getIndex(G->adj[u]) !=  -1) {
        insertBefore(G->adj[u], v);
    }else {
        append(G->adj[u], v);
    }
    G->size++;
}

 
/*
 * BFS()
 * Runs the BFS algorithm on the Graph G with source s, setting the
 * color, distance, parent, and source fields of G accordingly.
 */
void BFS(Graph G, int s) {
    if( s < 1 || s > getOrder(G) ) {
        printf("Graph Error(12): BFS() called on out of bounds source\n");
        exit(1);
    }
    G->source = s;
    int i;
    for(i = 1; i <= getOrder(G); i++) {
        G->color[i] = 'W';
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
   
    int x, y;
   
    G->color[s] = 'G';
    G->distance[s] = 0;
    G->parent[s] = NIL;

    List Q = newList();
    append(Q, s);
    while(length(Q) > 0) {
        x = front(Q);
        deleteFront(Q);
        moveTo(G->adj[x], 0);
        while(getIndex(G->adj[x]) != -1) {
            y = getElement(G->adj[x]);
            if( G->color[y] == 'W') {
                G->color[y] = 'G';
                G->distance[y] = getDist(G, x) + 1;
                G->parent[y] = x;
                append(Q, y);
            }
            moveNext(G->adj[x]);
        }
        G->color[x] = 'B';
    }
    freeList(&Q);
}

/*
 * printGraph()
 * Prints the adjacency list representation of G to the file pointed 
 * to by out.
 */
void printGraph(FILE* out,Graph G) {
    int i;
    for(i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
    }
}

