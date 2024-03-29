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
__global__ void combineCubes(Hypercube *arrayOne,  Hypercube *arrayTwo, int N, int cubes);
__device__ bool similarCube(int *F, int *H);
__device__  int atomicAdd(int *address, int val);

DTYPE myScore(int density, int densityMax)
{

	//return the density score
	return (1.000000 - ((double)density/(double)densityMax));
}

int maxx(int *W, int bins)
{
	//initialize variables
	int max = W[0];

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
		Hypercube *secondArray;


		//warm up gpus
		warmUpGPU();

		//calculate cuda error
		cudaError_t errCode=cudaSuccess;

		//allocate cuda memory
		cudaMallocManaged(&firstArray,cubes*sizeof(Hypercube));
		cudaMallocManaged(&secondArray,N*sizeof(Hypercube));

		//add the values to the cuda arrays
		for(int i = 0; i < cubes; i++)
		{
		firstArray[i].countings = sortArray[i]->countings;
		for(int j = 0; j < DIM; j++)
		{
		firstArray[i].coords[j]=sortArray[i]->coords[j];
		}
		}

		//add the coordinants to the device for reference later
		for(int i = 0; i < N; i++)
		{
		for(int j = 0; j < DIM; j++)
		{
			secondArray[i].coords[j] = wholeList[i]->coords[j];
		}
		}

		//setup blocks
		unsigned int totalBlocks = ceil((float)N/(float)1024);

		//initiate kernel
		combineCubes<<<totalBlocks,1024>>>(firstArray, secondArray, N, cubes);

		if(errCode != cudaSuccess){
		printf("Error code 1 %d\n",errCode);

		}

		//synchronize host and device
		errCode = cudaDeviceSynchronize();
		if(errCode != cudaSuccess)
		{
		printf("Error code at synchronize %d\n",errCode);
		}

		//add the location to the unique cubes after combine funct
		for(int i = 0; i < cubes; i++)
		{
		printf("Before [%d]\n",firstArray[i].countings);
		firstArray[i].loc = i;
		}

		//create an empty density array W
		int *W;

		//set up the density aray on the device
		cudaMallocManaged(&W,sizeof(double)*cubes);

		//add the density to each of the individual cubes
		for(int i = 0; i < cubes; i++)
		{
		W[i] = firstArray[i].countings;
		}

		//make the second array be the first array
		secondArray = firstArray;

		//synchronize host and device
		cudaDeviceSynchronize();

		//calculate neighborhood densities
		totalBlocks = ceil((float)cubes / (float)1024);
		neighborhood_density<<<totalBlocks,1024>>>(firstArray, secondArray, cubes, W);
		cudaDeviceSynchronize();

		//calclate the largest density value
		int Wmax = maxx(W, cubes);
		for(int i = 0; i < cubes; i++)
		{
		printf("After %d|",W[i]);
		printf("[%d][%d][%d]\n",firstArray[i].coords[0],firstArray[i].coords[1],firstArray[i].coords[2]);
		}

		//for reach datapoint within the dataset
			for(int index = 0; index < cubes; index++)
			{

			//calculate the score for that datapoint within hypercubes
			outlierArray[index] = myScore(W[index], Wmax);

			}

		//end for and free arrays
		cudaFree(W);
		free(sortArray);
		cudaFree(firstArray);
		cudaFree(secondArray);

		return cubes;
		//end program
}


__device__ bool similarCube(int *F, int *H)
{
	for(int i = 0; i < DIM; i++)
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
	unsigned int tid = threadIdx.x + blockIdx.x * blockDim.x;
	int blocks = 0;

	//processing
	if(tid < N)
	{
	for(blocks = 0; blocks < cubes; blocks++)
	{
		if(similarCube(arrayOne[blocks].coords,arrayTwo[tid].coords))
		{
		atomicAdd(&arrayOne[blocks].countings,1);
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
