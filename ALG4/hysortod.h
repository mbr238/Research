#ifndef HYSORTOD_H
#define HYSORTOD_H

//header files of create_hypercubes, construct, and neighborhood density
#include "hypercube.h"
#include "neighbor.h"
#include "params.h"


//prototypes
DTYPE myScore(DTYPE density, DTYPE densityMax)
{
	
	//return the density score
	return (1.000000 - (density/densityMax));
}

DTYPE max(DTYPE *W, int b)
{
	//initialize variables
	DTYPE max = W[0];
	//loop through the array
	for(int i = 0; i < pow(b-1,DIM); i++)
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
void HYsortOD(int bins, DTYPE *outlierArray, DTYPE **dataset, Hypercube **array, int N)
{
	//initialize program
	DTYPE values[DIM];
	DTYPE density, result;	

	//processing
		//create the hypercubes
			for(int i = 0; i < N; i++)
			{
				for(int k = 0; k < DIM; k++)
				{
				values[k] = dataset[i][k];
				}
				create_Hypercubes( values, array, bins);	
			}		
		
		
		//sort the hypercubes
		//probably dont need since the array has them next to eachother based on points anyways
		
		//create an empty density array W
		DTYPE *W = (DTYPE*)malloc(sizeof(DTYPE*)*pow(bins-1,DIM));
	    
		//initialize the density arrayss to 0s
		for(int i = 0; i < pow(bins-1,DIM); i++)
		{
				W[i] = 0.0;
		}
		
		
		//iterate through the hypercube array for each hypercube
		for(int i = 0; i < pow(bins-1,DIM); i++)
		{
			
				//if the hypercube is initialized
				if(array[i] != NULL)
				{
					//calculate neighborhood density
					density = neighborhood_density(array, array[i], bins);
					
					//insert that density into the density  array	
					W[i] = density;
				}
				//otherwise it is not initialized	
				
		}
		
		//end for
	
		//calclate the largest density value
		DTYPE Wmax = max(W, bins);
		
		//for reach datapoint within the dataset
			for(int index = 0; index < pow(bins-1,DIM); index++)
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