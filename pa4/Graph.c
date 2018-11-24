//Graph.c
//Implementation for the Graph ADT
//written by Samuel Shin, sayshin@ucsc.edu, pa4

//#include "List.h"
#include "Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//constructors-destructors----------------------------------------------------------------------------------------------------------------------------------------------

typedef struct GraphObj
{
	List* neighbors;
	char* color;
	int* parent;
	int* distance;
	int order;
	int size;
	int source;	
}GraphObj;

Graph newGraph(int n)
{
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->neighbors = malloc(sizeof(*G->neighbors) * (n + 1));
	for (int i = 1; i <= n; i++)
	{
		G->neighbors[i] = newList();
	}
	G->color = malloc(sizeof(char) * (n + 1));
	G->parent = malloc(sizeof(int) * (n + 1));
	G->distance = malloc(sizeof(int) * (n + 1));
	for (int j = 1; j <= n; j++)
	{
		G->distance[j] = 0;
	}
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

void freeGraph(Graph* pG)
{
	if (pG != NULL && *pG != NULL)
	{
		for (int i = 1; i <= (*pG)->order; i++)
		{
			//freeList((List*)(*pG)->neighbors[i]);
			clear((*pG)->neighbors[i]);
			free((*pG)->neighbors[i]);	
		}
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
	}	
	free(*pG);
	*pG = NULL;
}

//Access Methods--------------------------------------------------------------------------------------------------------------------------------------------------------

int getOrder(Graph G)
{
	return G->order;
}

int getSize(Graph G)
{
	return G->size;
}

int getSource(Graph G)
{
	if (G->source == NIL)
	{
		return NIL;
	}
	else 
	{
		return G->source;
	}
}

int getParent(Graph G, int u)
{
	if (G->source == NIL)
	{
		return NIL;
	}
	else if (u >= 1 && u <= getOrder(G))
	{
		return G->parent[u];
	}
	else 
	{
		printf("Graph error: calling getParent() on invalid vertex");
		exit(1);
	}
}

int getDist(Graph G, int u)
{
	if (G->source == NIL)
	{
		return INF;
	}
	else if (u >= 1 && u <= getOrder(G))
	{
		return G->distance[u];
	}
	else 
	{
		printf("Graph error: calling getDist() on invalid vertex");
		exit(1);
	}
	
}

void getPath(List L, Graph G, int u)
{
	if (G->source == NIL)
	{
		printf("Graph error: calling getPath() before BFS()");
		exit(1);
	}
	else if (u >= 1 && u <= getOrder(G))
	{
		//int len = sizeof(G->parent) / sizeof(G->parent[u]);
		if (u == G->source)
		{
			append(L, u);
		}
		else if (G->parent[u] != NIL)
		{
			getPath(L, G, G->parent[u]);
			append(L, u);
		}
		else 
		{
			append(L, NIL);
		}
	}
}

//Manipulation procedures-----------------------------------------------------------------------------------------------------------------------------------------------

void makeNull(Graph G)
{
	for (int i = 1; i <= getOrder(G) + 1; i++)
	{
		clear(G->neighbors[i]);
		G->color[i] = 'w';
		G->distance[i] = INF;
		G->parent[i] = NIL;
		//freeList(&(G->neighbors[i]));
	}
	G->source = NIL;
	G->size = 0;
}

void addEdge(Graph G, int u, int v)
{
	if ((u >= 1 && u <= getOrder(G)) && (v >= 1 && v <= getOrder(G)))
	{
		/*if (u == v)
		{
		}*/
		if (length(G->neighbors[u]) == 0)
		{
			append(G->neighbors[u], v);
			G->size++;
		}
		else
		{
			moveFront(G->neighbors[u]);
			while (index(G->neighbors[u]) >= 0)
			{
				if (get(G->neighbors[u]) > v)
				{
					insertBefore(G->neighbors[u], v);
					G->size++;
					break;
				}
				else
				{
					moveNext(G->neighbors[u]);
					if (index(G->neighbors[u]) < 0)
					{
						append(G->neighbors[u], v);
						G->size++;
						break;
					}
				}
			}
		}
		
		if (length(G->neighbors[v]) == 0)
		{
			append(G->neighbors[v], u);
		}
		else 
		{
			moveFront(G->neighbors[v]);
                	while (index(G->neighbors[v]) >= 0)
                	{
                        	if (get(G->neighbors[v]) > u)
                        	{
                                	insertBefore(G->neighbors[v], u);
                                	break;
                        	}
                        	else
                        	{
                                	moveNext(G->neighbors[v]);
                                	if (index(G->neighbors[v]) < 0)
                                	{
                                        	append(G->neighbors[v], u);
                                        	break;
                                	}
                        	}
                	}
		}	
	}
	else 
	{
		printf("Graph error: calling addEdge() on invalid vertices");
		exit(1);
	}
}

void addArc(Graph G, int u, int v)
{
	if ((u >= 1 && u <= getOrder(G)) && (v >=1 && v <= getOrder(G)))
        {
                /*if (u == v)
                {
                }*/
		if (length(G->neighbors[u]) == 0)
		{
			append(G->neighbors[u], v);
			G->size++;
		}
		else 
		{
                	moveFront(G->neighbors[u]);
                	while (index(G->neighbors[u]) >= 0)
               		{
                        	if (get(G->neighbors[u]) > v)
                        	{
                                	insertBefore(G->neighbors[u], v);
                                	G->size++;
                                	break;
                        	}
                        	else
                        	{
                                	moveNext(G->neighbors[u]);
                                	if (index(G->neighbors[u]) < 0)
                                	{
                                        	append(G->neighbors[u], v);
                                        	G->size++;
                                        	break;
                                	}
                        	}
                	}
		}
	}
	else
        {
                printf("Graph error: calling addEdge() on invalid vertices");
                exit(1);
        }	
}

void BFS(Graph G, int s)
{
	G->source = s;
	List Q = newList();	
	for (int x = 1; x <= getOrder(G); x++)
	{
		G->color[x] = 'w';
		G->distance[x] = INF;
		G->parent[x] = NIL;
	}
	G->color[s] = 'g';
	G->distance[s] = 0;
	G->parent[s] = NIL;
	append(Q, s);
	while (length(Q) > 0)
	{
		moveFront(Q);
		int x = get(Q);
		deleteFront(Q);
		moveFront(G->neighbors[x]);
		while(index(G->neighbors[x]) >= 0)
		{
			int y = get(G->neighbors[x]);
			
			if (G->color[y] == 'w')
			{
				G->color[y] = 'g';
				G->distance[y] = (G->distance[x]) + 1;
				G->parent[y] = x;
				append(Q, y);
			}
			moveNext(G->neighbors[x]);
		}
		G->color[x] = 'b';
	}
	freeList(&Q);
}

//Other operations------------------------------------------------------------------------------------------------------------------------------------------------------

void printGraph(FILE* out, Graph G)
{
	if (G == NULL)
	{
		printf("Graph error: calling printGraph() on NULL Graph reference");
		exit(1);
	}	
	
	for (int i = 1; i <= getOrder(G); i++)
	{
		fprintf(out, "%d", i);
		fprintf(out, "%s", ": ");
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}
