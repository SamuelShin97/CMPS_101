/*GraphTest.java
 *This file is used for testing the Graph ADT and checks the Graph's methods as I personally needed when debugging.
 *Samuel Shin, sayshin@ucsc.edu, pa4
 */

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	Graph A = newGraph(100);

	addEdge(A, 64, 4);
	addEdge(A, 64, 3);
	addEdge(A, 42, 2);
	addEdge(A, 2, 64);
	addEdge(A, 4, 2);
	addEdge(A, 3, 42);
	BFS(A, 64);

	int d = getDist(A, 42);
	printf("%d", d);

	BFS(A, 4);
	int e = getDist(A, 42);
	printf (" %d", e);

        BFS(A, 3);
	List L = newList();
        getPath(L, A, 64);
	printf("\n");
	printList(stdout, L);

	printf("\n");
	//makeNull(A);
	//printGraph(stdout, A);
	
	Graph B = newGraph(100);
	List list = newList();
	addArc(B, 64, 4);
        addArc(B, 64, 3);
        addArc(B, 42, 2);
        addArc(B, 2, 64);
        addArc(B, 4, 2);
        addArc(B, 3, 42);
        BFS(B, 3);
        getPath(list, B, 64);
	printList(stdout, list);

	freeGraph(&A);
	freeGraph(&B);
}
