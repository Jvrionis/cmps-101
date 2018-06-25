/**************************************************************
 * James Michael Vrionis
 * JVrionis
 * 3-2-17
 * Programming Assingment 4
 * 
 * Graph.h: Header file for Graph ADT that exports the 
 * following functions.
 *  
 *************************************************************/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define INF -2  /* (INFINITY) - Any negative int value */
#define NIL -1  /* (UNDEF) - Any non-positive int value */

#include "List.h"

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

/* getSource():
 * Returns the source vertex most recently used in function BFS(), or
 * NIL if BFS() has not yet been called.
 */
int getSource(Graph G);

/* getParent():
 * Pre: 1<=u<=getOrder(G)
 * Will return the parent of vertex u in the Breadth-First tree 
 * created by BFS(), or NIL if BFS() is not yet been called.
 */
int getParent(Graph G, int u);

/* getDist():
 * Pre: 1<=u<=getOrder(G)
 * Returns the distance from the most recent BFS source to vertex u
 * or INF if BFS() has not yet been called.
 */
int getDist(Graph G, int u);

/* getPath():
 * Pre: getSource(G) != NIL ||   1<=u<=getOrder(G)
 * Append to the List L the vertices of a shortest path in G from 
 * source to u, or appends to L the value NIL if no such path exists.
 */ 
void getPath(List L, Graph G, int u);


/* makeNull():
 * Deletes all edges of G, restoring it to its original (no edge) 
 * state. 
 */
void makeNull(Graph G);

/* addEdge():
 * Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
 * Inserts a new edge joining u to v, i.e. u is added to the adjacency
 * List of v and v to the adjacency List of u.
 */
void addEdge(Graph G, int u, int v);

/* addArc():
 * Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
 * Inserts a new directed edge from u to v, i.e. v is added to the 
 * adjacency List of u (but not u to the adjacency List of v).
 */
void addArc(Graph G, int u, int v);

/* BFS():
 * Runs the BFS algorithm on the Graph G with source s, setting the
 * color, distance, parent, and source fields of G accordingly.
 */
void BFS(Graph G, int s);

/*** Other operations ***/

/* printGraph()
 * Prints the adjacency list representation of G to the file pointed 
 * to by out.
 */
void printGraph(FILE* out,Graph G);

#endif
