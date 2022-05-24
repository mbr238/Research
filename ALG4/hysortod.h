#ifndef HYSORTOD_H
#define HYSORTOD_H

//header files of create_hypercubes, construct, and neighborhood density
#include "hypercube.h"

const int N = 515900;
const int DIM = 2;
const double length = 0.20; // this is 1/b	

//prototypes
double myScore(double density, double densityMax)
{
	//return the score
	return 1 - (density/densityMax);
}

															//fix with binary tree root
double neighborhood_density(Hypercube *array, int countings, Hypercube *root, int position, int dimension)
{
	
	return 0.0; // temp stub routine
}

												//fix with binary tree root
void construct( Hypercube *array, int minSplit, Hypercube *root, int constant)
{
	printf("Constructing\n");
}


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
void HYsortOD(int bins, int minSplit, double **outlierArray, double **dataset, double length)
{
	//initialize program
	double values[2];
	Hypercube *array[b][b];
	int position = 0;
	
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
					create_Hypercubes( values, length, array);	
			}	
		
		//construct the binary tree with hypercubes
			Hypercube* root = NULL;
			construct( array, minSplit, root, 1);
	
		//create an empty density array W
		double W[b][b];
				
		//iterate through the hypercube array for each hypercube
		for(int i = 0; i < b; i++)
		{
			for(int j = 0; j < b; j++)
			{
				if(array[i][j] != NULL)
				{
					//calculate neighborhood density
					double density = 2;
					density = neighborhood_density(array, array[i][j]->countings, root, position, 1);
					
					//insert that density into the density  array	
					W[i][j] = density;
					
				}
			
			
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
				//calculate the score for that datapoint within hypercubes
				double result;
				result = myScore(W[index][j], Wmax);
				
				//insert that score into the outlier array
				outlierArray[index][j] = result;
				}
			}
		//end for
		
		//end program
}






#endif