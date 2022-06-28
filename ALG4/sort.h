#ifndef SORT_H
#define SORT_H
#include <stdbool.h>
#include "hypercube.h"

void swap( Hypercube **arr, int i, int j)
{
	Hypercube *a;
	a = arr[i];
	arr[i] = arr[j];
	arr[j] = a;
}

bool compareCubes(Hypercube *H, Hypercube *F)
{
	
	for(int i = 0; i < DIM; i++)
	{
		if(H->coords[i] < F->coords[i] )
		{
			return true;
		}
		
	}
	return false;
}


void sort(Hypercube **array, int N)
{
	
		for(int i = 0; i < N; i++)
		{
			if(array[i] == NULL)
			{
				break;
			}
			for(int j = 1; j < N; j++)
			{
				if(array[j] == NULL)
				{
					break;
				}
				if(compareCubes(array[i], array[j]))
				{
					swap(array, i, j);
				}
			}
		
		}
	
}



//sort the hypercubes in ascending order

void sortCube(Hypercube **array, Hypercube **sortArray, int N)
{
	int index = 0;
	int cubeIndex = 0;
	
	for(cubeIndex = 0; cubeIndex < N; cubeIndex++)
	{
		if(array[cubeIndex] == NULL && array[cubeIndex + 1] != NULL)
		{
			sortArray[index] = array[cubeIndex + 1];
			index++;
			cubeIndex++;
		}
		else if(array[cubeIndex] == NULL && array[cubeIndex + 1] == NULL)
		{
			break;
		}
		else
		{
			 
			sortArray[index] = array[cubeIndex];
			index++;
			
		}
		
	}
	
	index++;
	sortArray[index] = NULL;
	
}








#endif