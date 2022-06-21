#ifndef NEIGHBOR_H
#define NEIGHBOR_H

//header files
#include <time.h>
#include <stdbool.h>
#include "params.h"


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


DTYPE neighborhood_density(Hypercube **array, Hypercube *H, int N)
{
	//initialize program
	DTYPE density = 0;
	
	//processing
		//initialize density with the first density/hypercube countins
		density = H->countings;
		
		
		
			//traverse the hypercube array
			for(int k = 0; k < N; k++)
			{
				for(int i = k - 1; i >= 0; i--)
				{
					if(!isProspective(array[k], H))
					{
						break;
					}
					//check if the hypercubes are immediate
					if( array[k] != NULL && array[k] != H && isImmediate(H, array[k]) )
					{
						//if they are then add that cubes contings to the original density
						density = density + array[k]->countings;
						
					}	
				}

				for(int i = 0; i >= 0; i++)
				{
					if(!isProspective(array[k], H))
					{
						break;
					}
					//check if the hypercubes are immediate
					if( array[k] != NULL && array[k] != H && isImmediate(H, array[k]) )
					{
						//if they are then add that cubes contings to the original density
						density = density + array[k]->countings;
						
					}	
				}



				
					//end if loop
			}
			
			//end for loop
	//return the neighborhood density
	return density;
}









#endif