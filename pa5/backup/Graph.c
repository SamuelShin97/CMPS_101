//Graph.c
//Contains the implementation for the Graph ADT
//written by Samuel Shin, sayshin@ucsc.edu, pa5

//#include "List.h"
#include "Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void visit(Graph G, List S, int v, int back);

//constructors-destructors----------------------------------------------------------------------------------------------------------------------------------------------

typedef struct GraphObj
{
	List* neighbors;
	char* color;
	int* parent;
	int* discover;
	int* finish;
	int order;
	int size;
	int time;
}GraphObj;

Graph newGraph(int n)
{
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
	for (int i = 1; i <= n; i++)
	{
		G->neighbors[i] = newList();
	}
	G->color = calloc((n + 1), sizeof(char));
	G->parent = calloc((n+1), sizeof(int));
	G->discover = calloc((n+1), sizeof(int));
	G->finish = calloc((n+1), sizeof(int));
	for (int j = 1; j <= n; j++)
	{
		G->discover[j] = UNDEF;
		G->finish[j] = UNDEF;
	}
	G->order = n;
	G->size = 0;
	G->time = 0;
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
		free((*pG)->discover);
		free((*pG)->finish);
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

int getParent(Graph G, int u)
{
	if (u == NIL)
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

int getDiscover(Graph G, int u)
{
	if (G->discover[1] == UNDEF)
	{
		return UNDEF;
	}
	if (u >= 1 && u <= getOrder(G))
	{
		return G->discover[u];
	}
	else 
	{
		printf("Graph error: calling getDiscover() on invalid vertex");
		exit(1);
	}
	
}

int getFinish(Graph G, int u)
{
	if (G->discover[1] == UNDEF)
	{
		return UNDEF;
	}
	if (u >= 1 && u <= getOrder(G))
	{
		return G->finish[u];
	}
	else
	{
		printf("Graph error: calling getFinish() on invalid vertex");
		exit(1);
	}
}


//Manipulation procedures-----------------------------------------------------------------------------------------------------------------------------------------------

void makeNull(Graph G)
{
	for (int i = 1; i <= getOrder(G) + 1; i++)
	{
		clear(G->neighbors[i]);
		G->color[i] = 'w';
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		G->parent[i] = NIL;
		//freeList(&(G->neighbors[i]));
	}
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

void DFS(Graph G, List S)
{
	G->time = 0;
	int b = back(S);
	int thisCase = 0;
	if (length(S) == getOrder(G))
	{
		for (int x = 1; x <= getOrder(G); x++)
		{
			G->color[x] = 'w';
			G->parent[x] = NIL;
			G->discover[x] = UNDEF;
			G->finish[x] = UNDEF;	
		}
		
		for (int i = 1; i <= getOrder(G); i++)
		{
			int x = front(S);
			if (b != x)
			{
				deleteFront(S);
			}
			else 
			{
				thisCase = 1;
			}
			
			if (G->color[x] == 'w')
			{
				visit(G, S, x, b);
			}		
		}
		if (thisCase == 1)
		{
			deleteFront(S);
		}
	}
	else
	{
		printf("Graph error: calling DFS() on different size list and and graph");
		exit(1);
	}
}

void visit(Graph G, List S, int v, int back)
{
	G->color[v] = 'g';
	G->discover[v] = ++G->time;
	moveFront(G->neighbors[v]);
	while (index(G->neighbors[v]) >= 0)
	{
		int y = get(G->neighbors[v]);
		if (G->color[y] == 'w')
		{
			G->parent[y] = v;
			visit(G, S, y, back);
		}
		moveNext(G->neighbors[v]);
	}	
	G->color[v] = 'b';
	G->finish[v] = ++G->time;

	moveFront(S);
	
	while (get(S) != back)
	{
		moveNext(S);
	}	
	insertAfter(S, v);
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

Graph transpose(Graph G)
{
	Graph T = newGraph(getOrder(G));
	
	for (int i = 1; i <= getOrder(G); i++)
	{
		for (int j = 1; j <= getOrder(G); j++)
		{
			moveFront(G->neighbors[j]);
			while (index(G->neighbors[j]) >= 0)
			{
				int x = get(G->neighbors[j]);
				if (i == x)
				{
					append(T->neighbors[i], j);
				}
				moveNext(G->neighbors[j]);
			}
		}
	}
	return T;	
}

Graph copyGraph(Graph G)
{
	Graph C = newGraph(getOrder(G));
	
	for (int i = 1; i <= getOrder(G); i++)
	{
		C->neighbors[i] = copyList(G->neighbors[i]);
	}
	
	return C;
}
