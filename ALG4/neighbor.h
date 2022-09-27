#ifndef NEIGHBOR_H
#define NEIGHBOR_H

//header files
#include <time.h>
#include <stdbool.h>
#include "params.h"
#include "hypercube.h"
#include "omp.h"

bool isProspective(Hypercube *H, Hypercube *F)
{
	return (abs(H->coords[0] - F->coords[0]) <= 1);
	
}



//function to calculate neighboring hypercubes
bool isImmediate(Hypercube *H, Hypercube *F)
{
	//initialize varaibles

	for(int i = 0; i < DIM; i++)
	{
		if( abs(H->coords[i] - F->coords[i]) > 1)
		{
			return false;
		}
	}

	return true;
}


void neighborhood_density(Hypercube **array, int N, DTYPE *W)
{
	//initialize program
	omp_set_num_threads(NTHREADS);
	
	//processing
			//traverse the hypercube array
			#pragma omp parallel
			{	
			#pragma omp for
			for(int i = 0; i < N; i++)
			{
				W[i] = array[i]->countings;
				
				for(int k = i - 1; k >= 0; k--)
				{
					if(!isProspective(array[i],array[k]))
					{
						break;
					}
					if(isImmediate(array[i],array[k]))
					{
						W[i] += array[k]->countings;
					}	
				}	
				
				for(int k = i + 1; k < N; k++)
				{
					if(!isProspective(array[i],array[k]))
					{
						break;
					}
					if(isImmediate(array[i],array[k]))
					{
						W[i] += array[k]->countings;
					}
					}
					
				
				}
				
			}
			//end for loop
	//return the neighborhood density

}









#endif