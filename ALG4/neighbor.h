
#ifndef NEIGHBOR_H
#define NEIGHBOR_H

//header files
#include <time.h>
#include <stdbool.h>
#include "params.h"
#include "hypercube.h"
#include "omp.h"

__device__ bool isProspective(int *H, int *F)
{
	return (abs(H[0] - F[0]) <= 1);

}



//function to calculate neighboring hypercubes
__device__ bool isImmediate(int *H, int *F)
{
	//initialize varaibles

	for(int i = 0; i < DIM; i++)
	{
		if( abs(H[i] - F[i]) > 1)
		{
			return false;
		}
	}

	return true;
}


__global__ void neighborhood_density(Hypercube *array, int N, int *W)
{
	//initialize program
	int tid = threadIdx.x;// + (blockIdx.x*blockDim.x);
	//processing
			//traverse the hypercube array
			if(tid < N)
			{
			//for(int i = 0; i < N; i++)
			//{
				W[tid] = array[tid].countings;

				//for(int k = i - 1; k >= 0; k--)
				//{
					/*if(i > 1)
					{
					if(!isProspective(array[i].coords,array[N - tid - 1].coords))
					{
						return;
					}
					if(isImmediate(array[i].coords,array[N - tid - 1].coords))
					{
						atomicAdd(&W[i], array[N - tid - 1].countings);
					}
					}

				//}
				//for(int k = i + 1; k < N; k++)
				//{
					if(!isProspective(array[i].coords,array[tid].coords))
					{
						return;
					}
					if(isImmediate(array[i].coords,array[tid].coords))
					{
						atomicAdd(&W[i], array[tid].countings);
					}
			}*/
			if(isImmediate(array[tid].coords,array[tid].coords) && array[tid].loc != array[tid].loc)
			{
			atomicAdd(&W[tid], array[tid].countings);
			return;
			}
			}
				//}
			//}
	return;
			//end for loop
	//return the neighborhood density

}









#endif
