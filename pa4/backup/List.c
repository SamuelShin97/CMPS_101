//List.c
//Implementation for the List ADT
//written by Samuel Shin, sayshin@ucsc.edu, pa2

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structs-------------------------------------------------------------------------------------------

//private NodeObj type
typedef struct NodeObj
{
	int data;
	struct NodeObj* next;
	struct NodeObj* previous;
}NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj
{
	int length;
	int index;
	Node front;
	Node back;
	Node cursor;
}ListObj;

//Constructors-Destructors--------------------------------------------------------------------------

//newNode()
//Returns a reference to a new Node object. Initializes data,next, and previous fields.
//private.
Node newNode(int data)
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->previous = NULL;
	return N;
}

//freeNode()
//Frees heap memory pointed to by *pN, sets *pN to NULL
//private

void freeNode(Node* pN)
{
	if (pN != NULL && *pN != NULL)
	{
		free(*pN);
		*pN = NULL;
	}
}

//NewList()
//returns a reference to new empty List object

List newList(void)
{
	List L;
	L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L-> index = -1;
	return L;
}

//freeList()
//frees all heap memory associated with List *pL and sets *pL to NULL
void freeList (List* pL)
{
	if (pL != NULL && (*pL) != NULL)
	{
		clear(*pL);
		free(*pL);
		pL = NULL;
	}
		
}

//access functions------------------------------------------------------------------------------------------------------------------------------------------------------


int length(List L)
{
	if (L == NULL)
	{
		printf("List Error: calling length(List L) on NULL List reference");
		exit(1);
	}
	else 
		return L->length;
}

int index(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling index(List L) on NULL List reference");
                exit(1);
        }
	if (L->cursor != NULL)
	{
		return L->index;
	}
	else 
		return -1;
}

int front(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling front(List L) on NULL List reference");
                exit(1);
        }
	if (L->length > 0)
	{
		return L->front->data;
	}
	return -1;	
}

int back(List L)
{
        if (L == NULL)
        {
                printf("List Error: calling back(List L) on NULL List reference");
                exit(1);
        }
        if (L->length > 0)
        {
                return L->back->data;
        }
	return -1;
}

int get(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling get(List L) on NULL List reference");
                exit(1);
        }
	if (L->length > 0 && L->index >= 0)
	{
		return L->cursor->data;
	}
	else 
		return -1;
}


int equals(List A, List B)
{
	Node N, M;
	if (A == NULL || B == NULL)
        {
                printf("List Error: calling equals(List A, List B) on NULL List reference");
                exit(1);
        }
	if (A->length != B->length)
	{
		return 0;
	}
	else 
	{
		N = A->front;
		M = B->front;
		while (N != NULL || M != NULL)
		{
			if (N->data != M->data)
			{
	
			return 0;
			}
			N = N->next;
			M = M->next;
		}
		return 1;
	}
}

//Manipulation procedures---------------------------------------------------------------------------

void clear(List L)
{
	
	if (L == NULL)
        {
                printf("List Error: calling clear(List L) on NULL List reference");
                exit(1);
        }
	
	
	Node N = L->front;
	Node temp;
	while (N != NULL)
	{
		temp = N;
		N = N->next;
		freeNode(&temp);	
	}	

	L->length = 0;
	L->index = -1;
	L->front = NULL;		
	L->back = NULL;
	L->cursor = NULL;
	
	
}

void moveFront(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling moveFront(List L) on NULL List reference");
                exit(1);
        }
	if (L->length > 0)
	{
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling moveBack(List L) on NULL List reference");
                exit(1);
        }
	if (L->length > 0)
	{
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

void movePrev(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling movePrev(List L) on NULL List reference");
                exit(1);
        }
	if (L->cursor != NULL && L->cursor != L->front)
	{
		L->cursor = L->cursor->previous;
		L->index--;
	}
	else if (L->cursor != NULL && L->cursor == L->front)
	{
		L->cursor = NULL;
		L->index = -1;
	}
	else if (L->cursor == NULL)
	{}
}

void moveNext(List L)
{
        if (L == NULL)
        {
                printf("List Error: calling moveNext(List L) on NULL List reference");
                exit(1);
        }
        if (L->cursor != NULL && L->cursor != L->back)
        {
                L->cursor = L->cursor->next;
		L->index++;
        }
        else if (L->cursor != NULL && L->cursor == L->back)
        {
                L->cursor = NULL;
		L->index = -1;
        }
	else if (L->cursor == NULL)
	{}
}

void prepend(List L, int data)
{
	if (L == NULL)
        {
                printf("List Error: calling prepend(List L, int data) on NULL List reference");
                exit(1);
        }
	if (L->length > 0)
	{
		Node N = newNode(data);
		L->front->previous = N;
		N->next = L->front;
		L->front = N;
		L->length++;
	}
	else 
	{
		Node N = newNode(data);
		L->front = N;
		L->back = N;
		L->length++;
	}

	if (L->cursor != NULL)
	{
		L->index++;
	}
}

void append(List L, int data)
{
	if (L == NULL)
        {
                printf("List Error: calling append(List L, int data) on NULL List reference");
                exit(1);
        }	
	if (L->length > 0)
	{
		Node N = newNode(data);
		L->back->next = N;
		N->previous = L->back;
		L->back = N;
		L->length++;
	}
	else 
	{
		Node N = newNode(data);
		L->front = N;
		L->back = N;
		L->length++;
	}
	if (L->cursor == L->back)
	{
		L->index++;
	}
}

void insertBefore(List L, int data)
{
	if (L == NULL)
        {
                printf("List Error: calling insertBefore(List L, int data) on NULL List reference");
                exit(1);
        }
	if (L->length > 0 && L->index >= 0)
	{
		if (L->cursor == L->front)
		{
			prepend(L, data);
		}
		else 
		{
			Node N = newNode(data);
			L->cursor->previous->next = N;
			N->previous = L->cursor->previous;
			N->next = L->cursor;
			L->index++;
			L->length++;
		}
	}
}

void insertAfter(List L, int data)
{
	if (L == NULL)
        {
                printf("List Error: calling insertAfter(List L, int data) on NULL List reference");
                exit(1);
        }	
	if (L->length > 0 && L->index >= 0)
	{
		if (L->cursor == L->back)
		{
			append(L, data);
		}
		else 
		{
			Node N = newNode(data);
			L->cursor->next->previous = N;
			N->next = L->cursor->next;
			N->previous = L->cursor;
			L->cursor->next = N;
			L->length++;
		}
	}
}

void deleteFront(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling deleteFront(List L) on NULL List reference");
                exit(1);
        }
	if (L->length > 0)
	{
		if (L->length == 1)
		{
			clear(L);
			freeNode(&L->front);
		}
		else 
		{
			Node temp;
			temp = L->front;
			L->front = L->front->next;
			L->front->previous = L->front->previous->previous;
			freeNode(&temp);
			L->length--;
		}
	}
	if (L->index > 0)
	{
		L->index--;
	}
	else if (L->index == 0)
	{
		L->cursor = NULL;
		L->index = -1;
	}
}

void deleteBack(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling deleteBack(List L) on NULL List reference");
                exit(1);
        }	
	if (L->length > 0)
	{
		if (L->length == 1)
		{
			clear(L);
			freeNode(&L->back);
		}
		else 
		{
			Node temp;
			temp = L->back;
			L->back = L->back->previous;
			L->back->next = L->back->next->next;
			freeNode(&temp);
			L->length--;
		}
	}
	if (L->index == L->length)
	{
		L->cursor = NULL;
		L->index = -1;
	}
}

void delete(List L)
{
	if (L == NULL)

        {
                printf("List Error: calling delete(List L) on NULL List reference");
                exit(1);
        }
	if (L->length == 1 && L->index >= 0)
	{
		clear(L);
		freeNode(&L->front);
	}
	else if (L->length > 0 && L->index >= 0)
	{
		if (L->cursor == L->front)
		{
			deleteFront(L);
		}
		else if (L->cursor == L->back)
		{
			deleteBack(L);
		}
		else 
		{
			Node temp;
			temp = L->cursor;
			L->cursor->previous->next = L->cursor->next;
			L->cursor->next->previous = L->cursor->previous;
			freeNode(&temp);
			L->cursor = NULL;
			L->index = -1;
			L->length--;
		}
	}
}

void printList(FILE* out, List L)
{
	Node N;
	if (L == NULL)
        {
                printf("List Error: calling printList(List L) on NULL List reference");
                exit(1);
        }
	N = L->front;
	while (N != NULL)
	{
		if (N->next != NULL)
		{
			fprintf(out, "%d ", N->data);
			N = N->next;
		}
		else 
		{
			fprintf(out, "%d", N->data);
			N = N->next;
		}
	}
	freeNode(&N);
}

List copyList(List L)
{
	if (L == NULL)
        {
                printf("List Error: calling copyList(List L) on NULL List reference");
                exit(1);
        }
	List clone = newList();
	Node N = L->front;
	while (N != NULL)
	{
		append(clone, N->data);
		N = N->next;
	}
	freeNode(&N);
	return clone;
}
