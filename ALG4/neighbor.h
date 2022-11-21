
#ifndef NEIGHBOR_H
#define NEIGHBOR_H

//header files
#include <time.h>
#include <stdbool.h>
#include "params.h"
#include "hypercube.h"
#include "omp.h"

bool isProspective(int *H, int *F)
{
	return (abs(H[0] - F[0]) <= 1);
	
}



//function to calculate neighboring hypercubes
bool isImmediate(int *H, int *F)
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


void neighborhood_density(Hypercube *array, int N, DTYPE *W)
{
	//initialize program
	
	//processing
			//traverse the hypercube array
			for(int i = 0; i < N; i++)
			{
				W[i] = array[i].countings;
				
				for(int k = i - 1; k >= 0; k--)
				{
					if(!isProspective(array[i].coords,array[k].coords))
					{
						break;
					}
					if(isImmediate(array[i].coords,array[k].coords))
					{
						W[i] += array[k].countings;
					}	
				}	
				
				for(int k = i + 1; k < N; k++)
				{
					if(!isProspective(array[i].coords,array[k].coords))
					{
						break;
					}
					if(isImmediate(array[i].coords,array[k].coords))
					{
						W[i] += array[k].countings;
					}
					}
					
				
				}
			
			//end for loop
	//return the neighborhood density

}









#endif
