#ifndef NEIGHBOR_H
#define NEIGHBOR_H
#include <time.h>
#include <stdbool.h>


//function to calculate neighboring hypercubes
bool isImmediate(Hypercube *H, Hypercube *F)
{
	if( abs(H->x_coords - F->x_coords) <= 1 && abs(H->y_coords - F->y_coords) <= 1)
	{
		return true;
	}

	return false; // they are not neighbors
}


double neighborhood_density(Hypercube* array[][b], Hypercube *H)
{
	//initialize program
	double density = 0;
	
	//processing
		//initialize density with the first density/hypercube countins
		density = H->countings;
		
			//traverse the hypercube array
			for(int k = 0; k < b; k++)
			{
				for(int j = 0; j < b; j++)
				{
				if(array[k][j] != NULL)
				{
					//check if the hypercubes are immediate
					if( array[k][j] != H && isImmediate(H, array[k][j]))
					{
						//if they are then add that cubes contings to the original density
						density = density + array[k][j]->countings;
						
					}				
					//end if loop
					
				}
				}
			}

			//end for loop
	//return the neighborhood density
	return density;
}









#endif