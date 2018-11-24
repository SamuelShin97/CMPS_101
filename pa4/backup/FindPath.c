//FindPath.c
//This program acts like the client for the Graph ADT and in turn the List ADT as well. This program 
//will read in an input file and do two things. It will write to an output file the adjacency list 
//of the graph that it constructs from the input. And it will print a shortest path from a source 
//vertex to a target vertex using BFS.
//written by Samuel Shin, sayshin@ucsc.edu, pa4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#define MAX_LEN 1104 //this is the most lines one of the test scripts have (specifically infile6.txt)

void printPath(FILE* out, Graph G, int s, int x);

int main (int argc, char * argv[])
{
	FILE *in, *out;
	char line[MAX_LEN];
	int linenum = 0;
	
	if (argc != 3)
	{
		printf("Usage: %s <input file> <output file> \n", argv[0]);
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL)
	{
		printf("Unable to open file %s for reading \n", argv[1]);
		exit(1);
	}

	if (out == NULL)
	{
		printf("Unable to open file %s for reading \n", argv[2]);
		exit(1);
	}

	while (fgets(line, sizeof(line), in))
	{
		linenum++;
	}
	
	rewind(in);
	fclose(in);
	char* arr[linenum];
	int i = 0;
	in = fopen(argv[1], "r");

	if (in == NULL)
        {
                printf("Unable to open file %s for reading \n", argv[1]);
                exit(1);
        }

	while (fgets(line, sizeof(line), in) != NULL)
	{
		arr[i] = calloc(strlen(line) + 1, 1);
		strcpy(arr[i], line);
		i++;	
	}

	int len = sizeof(arr) / sizeof(arr[0]);

	
	int n = atoi(arr[0]);
	Graph G = newGraph(n);
	int firstZeros = 0;
	int secondZeros = 0;
	for (int a = 1; a < len; a++)
	{
		char* tok;
		tok = strtok(arr[a], " ");
		int loopCon = 0;
		while (loopCon == 0)
		{
			int e = atoi(tok);
			int f = atoi(strtok(NULL, " "));
			if (e == 0)
			{
				if (firstZeros == 1)
				{
					secondZeros = 1;
					break;
				}
				else
				{
					firstZeros = 1;
					printGraph(out, G);
					fprintf(out, "\n");
					break;
				}
			}

			else if (firstZeros == 0)
			{
				addEdge(G, e, f);
			}
			else
			{
				BFS(G, e);
				fprintf(out, "%s%d%s%d%s", "The distance from ", e, " to ", f, " is ");
				if (getDist(G, f) == INF)
				{
					fprintf(out, "%s", "infinity");
					fprintf(out, "\n");
					fprintf(out, "%s%d%s%d%s", "No ", e, "-", f, " path exists");
				}
				else 
				{
					fprintf(out, "%d", getDist(G, f));
					fprintf(out, "\n");
					fprintf(out, "%s%d%s%d%s", "A shortest ", e, "-", f, " path is: ");
					printPath(out, G, e, f);
				}
				if (a != len - 2)
				{
					fprintf(out, "\n");
					fprintf(out, "\n");
				}
			}
			loopCon++;
		}
		if (secondZeros == 1)
		{
			break;
		}
	}

	fclose(in);
	fclose(out);
	return(0);
}

void printPath(FILE* out, Graph G, int s, int x)
{
	if (x == s)
	{
		fprintf(out, "%d ", s);
	}
	else
	{
		printPath(out, G, s, getParent(G, x));
		fprintf(out, "%d ", x);
		
	}
}
