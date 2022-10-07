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
int HYsortOD(DTYPE *outlierArray, DTYPE **dataset, Hypercube **array, int N, int b)
{
	//initialize program	
	int cubes = 0;
	
	//processing
	
		//set the outlier array originally to 0s 
		for(int i = 0; i < N; i++)
		{
		outlierArray[i] = 0.0;
		}
		Hypercube **wholeList = (Hypercube**)malloc(sizeof(Hypercube)*N);	
		
		//create the hypercubes
		cubes = create_Hypercubes( dataset, b, N, array, wholeList);
		Hypercube **sortArray = (Hypercube**)malloc(sizeof(Hypercube)*cubes);
		
		Hypercube **arrays = NULL, **secondArray = NULL;
	
		cudaError_t errCode=cudaSuccess;
		
		//allocate cuda memory
		errCode=cudaMalloc((Hypercube**)&arrays, sizeof(*Hypercube)*cubes);
		errCode=cudaMalloc((Hypercube**)&secondArray, sizeof(*Hypercube)*N);
		
		//copy over datasets
		errCode=cudaMemcpy( arrays, array, sizeof(*Hypercube)*cubes, cudaMemcpyHostToDevice);
		errCode=cudaMemcpy( secondArray, wholeList, sizeof(*Hypercube)*N, cudaMemcpyHostToDevice);
		
		if(errCode != cudaSuccess)
		{
		printf("\nLast error: %d\n", errCode); 	
		}
		
		//setup blocks
		const unsigned int totalBlocks=ceil(cubes);
		printf("\ntotal blocks: %d",totalBlocks);
			
		//initiate kernel
		combineCubes<<<totalBlocks,1024>>>(arrays, secondArray, N, cubes);
		
		if(errCode != cudaSuccess){
		cout<<"Error afrer kernel launch "<<errCode<<endl;
		
		}
		
		//copy the array from gpu
		errCode=cudaMemcpy( sortArray, secondArray, sizeof(*Hypercube)*cubes, cudaMemcpyDeviceToHost);
		if(errCode != cudaSuccess) {
		cout << "\nError: getting result form GPU error with code " << errCode << endl; 
		}

		sortCube(array, sortArray, N, cubes);
		free(array);
	
		combineCubes(sortArray, wholeList, N, cubes);		
		sort(sortArray, cubes);		
		
		//create an empty density array W
		DTYPE *W = (DTYPE*)malloc(sizeof(DTYPE*)*cubes);
	    
		//initialize the density arrayss to 0s
		for(int i = 0; i < cubes; i++)
		{
				W[i] = 0.0;
		}
		
		
		//calculate neighborhood densities
		neighborhood_density(sortArray, cubes, W);
		
	
		//calclate the largest density value
		DTYPE Wmax = maxx(W, cubes);
		
		//for reach datapoint within the dataset
			for(int index = 0; index < cubes; index++)
			{
		
			//calculate the score for that datapoint within hypercubes
			outlierArray[index] = myScore(W[index], Wmax);
			
			}
			
		//end for
		free(W);
		free(sortArray);
		
		return cubes;
		//end program
}






#endif