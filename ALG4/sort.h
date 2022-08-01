#ifndef SORT_H
#define SORT_H
#include <stdbool.h>
#include "hypercube.h"
#include "params.h"

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
			for(int j = 0; j < N; j++)
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
		if(array[cubeIndex] == NULL)
		{
			for(int j = cubeIndex; j < N; j++)
			{
				if(array[j] != NULL)
				{
				cubeIndex = j;
				break;
				}
			}
		}
		if(array[cubeIndex] != NULL)
		{
			sortArray[index] = array[cubeIndex];
			index++;
		}
		
	}
	
	index++;
	sortArray[index] = NULL;
	
}
		
		
double mins(DTYPE otherVal, DTYPE value)
{
	if(otherVal < 0 || value < 0)
	{
		return 0;
	}
	if(value < otherVal)
	{
		return value;
	}
	return otherVal;
}
		
double maxs(DTYPE otherVal, DTYPE value)
{
	if(value > otherVal)
	{
		return value;
	}
	return otherVal;
}	


void normalize(DTYPE **dataset, double max, double min, int N)
{
	
	for(int i = 0; i < DIM - 1; i++)
	{
		double minVal = 1.7976931348623157E+308;
		double maxVal = 0.0;
		for(int j = 0; j < N; j++)
		{
			minVal = mins(dataset[j][i], minVal);
			maxVal = maxs(dataset[j][i], maxVal);
		}
		
		for(int k = 0; k < N; k++)
		{
			double value = (dataset[k][i] - minVal) / ( maxVal - minVal);
			if(value < 0)
			{
				dataset[k][i] = 0.0;
			}
			else
			{
			dataset[k][i] = value;
			}
		}
		
	}
	
}






#endif