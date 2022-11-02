#ifndef HYSORTOD_H
#define HYSORTOD_H

//header files of create_hypercubes, construct, and neighborhood density
#include "hypercube.h"
#include "neighbor.h"
#include "params.h"
#include <math.h>
#include "sort.h"
#include <cuda.h>


//prototypes
void warmUpGPU();
__global__ void combineCubes(Hypercube *array,  Hypercube *wholeList, int N, int cubes);
__device__ bool similarCube(int *F, int *H);

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
		Hypercube **wholeList = (Hypercube**)malloc(sizeof(Hypercube*)*N);

		//create the hypercubes
		cubes = create_Hypercubes( dataset, b, N, array, wholeList);
		Hypercube **sortArray = (Hypercube**)malloc(sizeof(Hypercube*)*cubes);
		sortCube(array, sortArray, N, cubes);
                free(array);

		//create cuda arrays
		Hypercube *firstArray;
		Hypercube *secondArray, *sortArrays = (Hypercube*)malloc(sizeof(Hypercube*)*cubes);

		//warm up gpus
		warmUpGPU();

		//calculate cuda error
		cudaError_t errCode=cudaSuccess;

		//allocate cuda memory	
		cudaMallocManaged(&firstArray,cubes*sizeof(Hypercube));
		cudaMallocManaged(&secondArray,N*sizeof(Hypercube));

		for(int i = 0; i < cubes; i++)
		{
		firstArray[i].countings = sortArray[i]->countings;
		//cudaMallocManaged(&firstArray[i].coords,sizeof(int)*DIM);
		for(int j = 0; j < DIM; j++)
		{
		firstArray[i].coords[j]=sortArray[i]->coords[j];
		}
		}

		for(int i = 0; i < N; i++)
		{
		//cudaMallocManaged(&secondArray[i].coords,sizeof(int)*DIM);
		for(int j = 0; j < DIM; j++)
		{
			secondArray[i].coords[j] = wholeList[i]->coords[j];
		}
		}

		//setup blocks
		const unsigned int totalBlocks=ceil(cubes);
		printf("\ntotal blocks: %d\n",totalBlocks);

		//initiate kernel
		combineCubes<<<totalBlocks,1024>>>(firstArray, secondArray, N, cubes);

		if(errCode != cudaSuccess){
		printf("Error code 1 %d\n",errCode);

		}

		//copy the array from gpu
		sortArrays = firstArray;

		for(int i = 0; i < cubes; i++)
		{
		printf("[%d]\n",firstArray[i].countings);
		}

		//deallocate device memory
		cudaFree(firstArray);
		cudaFree(secondArray);

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


__device__ bool similarCube(int *F, int *H)
{
	for(int i = 0; i < DIM - 1; i++)
	{
		if(abs(F[i] - H[i]) != 0)
		{
			return false;
		}
	}
	return true;
}


__global__ void combineCubes(Hypercube *arrayOne,  Hypercube *arrayTwo, int N, int cubes)
{
	//initialize variables
        int tid = threadIdx.x+(blockIdx.x*blockDim.x);
	
	//processing
	for(int i = 0; i < cubes; i++)
	{
	if(tid >= N)
	{
	return;
	}
	for(int j = 0; j < N; j++)
	{
	if(similarCube(arrayOne[i].coords, arrayTwo[tid].coords))
	{
	arrayOne[i].countings= 10000;
	}
	}
	}
	return;
}

void warmUpGPU(){
	
cudaDeviceSynchronize();

return;
}

#endif
