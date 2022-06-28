#ifndef HYSORTOD_H
#define HYSORTOD_H

//header files of create_hypercubes, construct, and neighborhood density
#include "hypercube.h"
#include "neighbor.h"
#include "params.h"
#include <math.h>
#include "sort.h"


//prototypes
DTYPE myScore(DTYPE density, DTYPE densityMax)
{
	
	//return the density score
	return (1.000000 - (density/densityMax));
}

DTYPE maxx(DTYPE *W, int bins)
{
	//initialize variables
	DTYPE max = W[0];
	
	//loop through the array
	for(int i = 0; i < bins; i++)
	{
			if(W[i] > max)
			{
				//if the current val is greater than max replace it
				max = W[i];
			}
	}
	//return max
	return max;
}


//hysortod function retruns an array of outlierness in parameters
											//same size as dataset -- outlierarray
void HYsortOD(DTYPE *outlierArray, DTYPE **dataset, Hypercube **array, Hypercube **sortArray, int N, int b)
{
	//initialize program	

	
	//processing
	
		//set the outlier array originally to 0s 
		for(int i = 0; i < N; i++)
		{
		outlierArray[i] = 0.0;
		}
		
		
		//create the hypercubes
		create_Hypercubes( dataset, array, b, N);	
				
		//sort the hypercubes
		sortCube(array, sortArray, N);
		free(array);
		sort(sortArray, N);
		
		//create an empty density array W
		DTYPE *W = (DTYPE*)malloc(sizeof(DTYPE*)*N);
	    
		//initialize the density arrayss to 0s
		for(int i = 0; i < N; i++)
		{
				W[i] = 0.0;
		}
		
		//calculate neighborhood densities
			neighborhood_density(sortArray, N, W);

	
		//calclate the largest density value
		DTYPE Wmax = maxx(W, N);
		
		//for reach datapoint within the dataset
			for(int index = 0; index < N; index++)
			{
				//if the hypercube is initialized
				if(sortArray[index] != NULL)
				{
				//calculate the score for that datapoint within hypercubes
				outlierArray[index] = myScore(W[index], Wmax);
				
				}
				//otherwise hypercube is not initialized
				else
				{
				//set the spot in outlier array to 0 for not initialized
				outlierArray[index] = 0.0;
				
				}
			}
		//end for
		free(W);
		//end program
}






#endif