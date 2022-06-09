#ifndef NEIGHBOR_H
#define NEIGHBOR_H

//header files
#include <time.h>
#include <stdbool.h>
#include "params.h"

//function to calculate neighboring hypercubes
bool isImmediate(Hypercube *H, Hypercube *F)
{
	//initialize varaibles
	bool neighborFlag = true;

	for(int i = 0; i < DIM; i++)
	{
		if( abs(H->coords[i] - F->coords[i]) > 1)
		{
			return false;
		}
	}

	return neighborFlag;
}


DTYPE neighborhood_density(Hypercube **array, Hypercube *H, int bins)
{
	//initialize program
	DTYPE density = 0;
	
	//processing
		//initialize density with the first density/hypercube countins
		density = H->countings;
		
			//traverse the hypercube array
			for(int k = 0; k <= pow(bins,DIM); k++)
			{
					//check if the hypercubes are immediate
					if( array[k] != NULL && array[k] != H && isImmediate(H, array[k]) )
					{
						//if they are then add that cubes contings to the original density
						density = density + array[k]->countings;
						
					}				
					//end if loop
			}
			
			//end for loop
	//return the neighborhood density
	return density;
}









#endif