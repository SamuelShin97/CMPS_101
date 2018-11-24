//FindComponents.c
//This program acts like the client for the Graph ADT and in turn the List ADT as well. This program 
//will read in an input file and do two things. It will write to an output file the adjacency list 
//of the graph that it constructed. It will then run DFS() on the graph and there will be an output
//list of descending finish times. The program will take the transpose of the graph and run DFS() 
//on the transpose using the list produced in the first run of DFS() to determine how DFS() is 
//run the second time. The program will finally print out the strongly connected components of the 
//original graph
//written by Samuel Shin, sayshin@ucsc.edu, pa5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 63 //this is the most lines one of the test scripts have (specifically infile6.txt)

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
	for (int a = 1; a < len; a++)
	{
		char* tok;
		tok = strtok(arr[a], " ");
		int e = atoi(tok);
		int f = atoi(strtok(NULL, " "));
		if (e == 0)
		{
			fprintf(out, "%s", "Adjacency list representation of G:");
			fprintf(out, "\n");
			printGraph(out, G);
			fprintf(out, "\n");
			break;
		}

		else
		{
			addArc(G, e, f);
		}
	}
	
	List S = newList();
	for (int i = 1; i <= getOrder(G); i++)
	{
		append(S, i);
	}
	
	DFS(G, S);
	Graph T = transpose(G);
	DFS(T, S);	

	moveBack(S);
	List temp = newList();
	int count = 1;
	int counter = 0;

	while(index(S) >= 0)
	{
		if (getParent(T, get(S)) == NIL)
		{
			counter++;
		}
		movePrev(S);
	}
	moveBack(S);
	fprintf(out, "%s%d%s", "G contains ", counter, " strongly connected components:");
	fprintf(out, "\n");
	
	while (index(S) >= 0)
	{
		if (getParent(T, get(S)) != NIL)
		{
			prepend(temp, get(S));
		}
		else
		{
			prepend(temp, get(S));
			fprintf(out, "%s%d%s", "Component ", count, ": ");
			printList(out, temp);
			fprintf(out, "\n");
			clear(temp);
			count++;
		}
		movePrev(S);
	}	
	fclose(in);
	fclose(out);
	return(0);
}

