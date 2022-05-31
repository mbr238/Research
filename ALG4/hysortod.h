#ifndef HYSORTOD_H
#define HYSORTOD_H

//header files of create_hypercubes, construct, and neighborhood density
#include "hypercube.h"
#include "neighbor.h"

const int N = 5159739;
const int DIM = 2;	

//prototypes
double myScore(double density, double densityMax)
{
	//return the score
	return (1.000000 - (density/densityMax));
}

												//fix with binary tree root
//void construct( Hypercube *array, int minSplit, Hypercube *root, int constant)
//{
//	printf("Constructing\n");
//} //comes from alg 2 when constructed


double max(double W[][b], int b)
{
	double max = W[0][0];
	
	for(int i = 0; i < b; i++)
	{
		for(int j = 0; j < b; j++)
		{
			if(W[i][j] > max)
			{
				max = W[i][j];
				
			}
		}
	}
	
	return max;
}


//hysortod function retruns an array of outlierness in parameters
	
											//same size as dataset -- outlierarray
void HYsortOD(int bins, int minSplit, double outlierArray[][b], double **dataset, double length)
{
	//initialize program
	double values[2];
	Hypercube* array[b][b];
	double result;	
	double density;	
	
	//initialize array to null initially
 	for(int i = 0; i < b; i++)
	{
		for(int j = 0; j < b; j++)
		{
		array[i][j] = NULL;
		}
		
	}
	
	//processing
		//create the hypercubes
			for(int i = 0; i < N; i++)
			{
					values[0] = dataset[i][0];
					values[1] = dataset[i][1];
					create_Hypercubes( values, length, array, bins);	
			}		
		
		
		//sort the hypercubes
		//probably dont need since the array has them next to eachother based on points anyways
		
		//create an empty density array W
		double W[b][b];
	
		//initialize the density arrayss to 0s
		for(int i = 0; i < b; i++)
		{
			for(int j = 0; j < b; j++)
			{
				W[i][j] = 0.0;
			}
		}
		
		
		//iterate through the hypercube array for each hypercube
		for(int i = 0; i < b; i++)
		{
			for(int j = 0; j < b; j++)
			{
				//if the hypercube is initialized
				if(array[i][j] != NULL)
				{
					//calculate neighborhood density
					density = neighborhood_density(array, array[i][j]);
					
					//insert that density into the density  array	
					W[i][j] = density;
					
				}
				//otherwise it is not initialized
		
			}
			
		}

		//end for
	
		//calclate the largest density value
		double Wmax = max(W, b);
		
		//for reach datapoint within the dataset
			for(int index = 0; index < b; index++)
			{
				for(int j = 0; j < b; j++)
				{
				//if the hypercube is initialized
				if(array[index][j] != NULL)
				{
				//calculate the score for that datapoint within hypercubes
				result = myScore(W[index][j], Wmax);
				
				//insert that score into the outlier array
				outlierArray[index][j] = result;
				}
				//otherwise hypercube is not initialized
				else
				{
				//set the spot in outlier array to 0 for not initialized
				outlierArray[index][j] = 0.0;
				}
				}
			}
		//end for

		//end program
}






#endif