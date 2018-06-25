/**************************************************************
 * Programming Assingment 5
 *
 * Graph.h: Header file for Graph ADT that exports the
 * following functions.
 *
 *************************************************************/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"

#define UNDEF -3 /* (INFINITY) - Any negative int value */
#define NIL -2 /* (UNDEF) - Any non-positive int value */

/*** Exported type ***/
typedef struct GraphObj* Graph;

/* newGraph():
 * Returns a reference to a new empty Graph.
 */
Graph newGraph(int n);

/* freeGraph():
 * Frees all heap memory associated with Graph pG, and sets *pG to NULL.
 */
void freeGraph(Graph* pG);

/* getOrder():
 * Returns the order of the graph.
 */
int getOrder(Graph G);

/* getSize():
 * Returns the size of the graph.
 */
int getSize(Graph G);

/* getParent():
 * Pre: 1<=u<=getOrder(G)
 * Will return the parent of vertex u in the Breadth-First tree
 */
int getParent(Graph G, int u);

/*
 * getDiscover():
 * Pre: 1<=u<=n=getOrder(G)
 * Returns time of discovery with respect to vertex u
 *
 */
int getDiscover(Graph G, int u);

/*
 * getFinish():
 * Pre: 1<=u<=n=getOrder(G)
 * Returns finish time with respect to vertex u
 *
 */
int getFinish(Graph G, int u);

/* addArc():
 * Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
 * Inserts a new directed edge from u to v, i.e. v is added to the
 * adjacency List of u (but not u to the adjacency List of v).
 */
void addArc(Graph G, int u, int v);

/* addEdge():
 * Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
 * Inserts a new edge joining u to v, i.e. u is added to the adjacency
 * List of v and v to the adjacency List of u.
 */
void addEdge(Graph G, int u, int v);

/* DFS():
 * Runs the DFS algorithm on the Graph G with source s, .
 */
void DFS(Graph G, List S);

/*
 * transpose():
 * Return a reference to a new graph obj containing
 * the Transpose of G
 */
Graph transpose(Graph G);

/*
 * copyGraph()
 * Returns a reference to a new graph which is a copy of G.
 */
Graph copyGraph(Graph G);

/* printGraph()
 * Prints the adjacency list representation of G to the file pointed
 * to by out.
 */
void printGraph(FILE *out, Graph G);

#endif
