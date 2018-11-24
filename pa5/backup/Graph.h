//Graph.h
//Graph header for the ADT Graph
//provides prototypes for the Graph ADT in Graph.c
//written by Samuel Shin, sayshin@ucsc.edu, pa4

#include <stdio.h>
#include "List.h"
#define UNDEF (-1)
#define NIL (0)
/*** Exported Type ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
