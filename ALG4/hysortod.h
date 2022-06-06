#ifndef HYSORTOD_H
#define HYSORTOD_H

//header files of create_hypercubes, construct, and neighborhood density
#include "hypercube.h"
#include "neighbor.h"
#include "params.h"


//prototypes
DTYPE myScore(DTYPE density, DTYPE densityMax)
{
	
	//return the score
	return (1.000000 - (density/densityMax));
}

												//fix with binary tree root
//void construct( Hypercube *array, int minSplit, Hypercube *root, int constant)
//{
//	printf("Constructing\n");
//} //comes from alg 2 when constructed


DTYPE max(DTYPE *W, int b)
{
	DTYPE max = W[0];
	
	for(int i = 0; i < pow(b,DIM); i++)
	{
			if(W[i] > max)
			{
				max = W[i];
				
			}
	}
	
	return max;
}


//hysortod function retruns an array of outlierness in parameters
	
											//same size as dataset -- outlierarray
void HYsortOD(int bins, int minSplit, DTYPE *outlierArray, DTYPE **dataset, DTYPE length)
{
	//initialize program
	DTYPE values[DIM];
	int arrSize = pow(b,DIM), i = 0;
	Hypercube* *array = malloc(sizeof(Hypercube*)*arrSize);
	DTYPE density, result;	
	
	//initialize array to null initially
 	for(i = 0; i <= arrSize; i++)
	{
	array[i] = NULL;
	
	}

	//processing
		//create the hypercubes
			for(int i = 0; i < N; i++)
			{
				for(int k = 0; k < DIM; k++)
				{
				values[k] = dataset[i][k];
				}
				create_Hypercubes( values, length, array, bins);	
			}		
		
		
		//sort the hypercubes
		//probably dont need since the array has them next to eachother based on points anyways
		
		//create an empty density array W
		DTYPE *W = malloc(sizeof(DTYPE*)*arrSize);
	
		//initialize the density arrayss to 0s
		for(int i = 0; i <= arrSize; i++)
		{
				W[i] = 0.0;
		}
		
		
		//iterate through the hypercube array for each hypercube
		for(int i = 0; i <= arrSize; i++)
		{
				//if the hypercube is initialized
				if(array[i] != NULL)
				{
					//calculate neighborhood density
					density = neighborhood_density(array, array[i]);
					
					//insert that density into the density  array	
					W[i] = density;
					
				}
				else
				{
					W[i] = 0.0;
				}
				//otherwise it is not initialized
			
		}
		
		//end for
	
		//calclate the largest density value
		DTYPE Wmax = max(W, b);
		
		//for reach datapoint within the dataset
			for(int index = 0; index <= arrSize; index++)
			{
				//if the hypercube is initialized
				if(array[index] != NULL)
				{
				//calculate the score for that datapoint within hypercubes
				result = myScore(W[index], Wmax);
				
				//insert that score into the outlier array
				outlierArray[index] = result;
				
				}
				//otherwise hypercube is not initialized
				else
				{
				//set the spot in outlier array to 0 for not initialized
				outlierArray[index] = 0.0;
				
				}
			}
		//end for
		
		//end program
}






#endif