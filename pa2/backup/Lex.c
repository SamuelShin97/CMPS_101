//Lex.c
//This program acts like the client for List.c and sorts the input file in lexographical order by line.
//Written by Samuel Shin, sayshin@ucsc.edu, pa2.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160
void sort(char* x, List y);

int main (int argc, char * argv[])
{
	FILE *in, *out;
	char line[MAX_LEN];
	int linenum;
	int temp = 0;
	int j = 0; 
	int pass, result;
	
	if (argc != 3)
	{
		printf("Usage: %s <input file> <output file> \n", argv[1]);
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
	int x = 0;
	in  = fopen(argv[1], "r");
	
	if (in == NULL)
        {
                printf("Unable to open file %s for reading \n", argv[1]);
                exit(1);
        }

	while (fgets(line, sizeof(line), in) != NULL)
	{
		arr[x] = calloc(strlen(line) + 1, 1);
		strcpy(arr[x], line);
		x++;
	}
       
	List list = newList();	
	//sort(*arr, list);
	int len =  (sizeof(arr) / sizeof(arr[0]));
	for (int i = 1; i < len; i++)
	{
		temp = i;
		j = i -1;
		moveBack(list);
		pass = 0;
		
		if (length(list) == 0)
		{
			result = strcmp(arr[j], arr[temp]);
			if (result <= 0)
			{
				prepend(list, j);
				append(list, temp);
				continue;
			}
			else 
			{
				prepend(list, temp);
				append(list, j);
				continue;
			}
		}
		while (j >= 0)
		{
			result = strcmp(arr[temp], arr[j]);
			if (result < 0)
			{
				movePrev(list);
			}
			if (index(list) == -1)
			{
				prepend(list, temp);
				pass = 1;
			}
			j--;
		}
		if (pass == 0)
		{
			insertAfter(list, temp);
		}
	}

	int a = 0;
	moveFront(list);
	while (index(list) >= 0)
	{
		a = get(list);
		fprintf(out, "%s", arr[a]);
		//fprintf(out, "\n");
		moveNext(list);
	}
	free(arr);
	freeList(&list);
	fclose(in);
	fclose(out);
	return (0);
}

/*void sort (char*A, List L)
{
	int temp = 0;
	int j = 0;
	int pass, result;
	//int len =  sizeof(A);
	//printf("%d", len);
	for (int i = 1; i < 12; i++)
	{
		temp = i;
		j = i - 1;
		moveBack(L);
		pass = 0;
		
		if (length(L) == 0)
		{
			char arrj[sizeof(A[j])];
                	char arrtemp[sizeof(A[temp])];
                	char strj[sizeof(A[j])];
                	char strtemp[sizeof(A[temp])];
                	*strj = A[j];
                	*strtemp = A[temp];
                	strcpy(arrj, strj);
                	strcpy(arrtemp, strtemp);

                	result = strcmp(arrj, arrtemp);
			if (result < 0)
			{
				prepend(L, j);
				append(L, temp);
				continue;
			}
			else 
			{
				prepend(L, temp);
				append(L, j);
				continue;
			}
		}
		while (j >= 0)
                {
			char arrj[sizeof(A[j])];
                	char arrtemp[sizeof(A[temp])];
                	char strj[sizeof(A[j])];
                	char strtemp[sizeof(A[temp])];
                	*strj = A[j];
                	*strtemp = A[temp];
                	strcpy(arrj, strj);
                	strcpy(arrtemp, strtemp);
			
                	result = strcmp(arrtemp, arrj);
                        if (result < 0)
                        {
                                movePrev(L);
                        }
                        if (index(L) == -1)
                        {
                                prepend(L, temp);
                                pass = 1;
                        }
                        j--;
                }
                if (pass == 0)
                {
                        insertAfter(L, temp);
                }	
	}
}*/

