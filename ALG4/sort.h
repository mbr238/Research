#ifndef SORT_H
#define SORT_H

#include "hypercube.h"

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