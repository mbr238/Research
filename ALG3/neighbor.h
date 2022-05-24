#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include <stdbool.h>
#include <math.h>

bool isImmediate(Hypercube *H, Hypercube *F)
{
	if( abs(H->x_coords - F->x_coords > 1) || abs(H->y_coords - F->y_coords > 1))
	{
		return false
	}

	return true; // they are neighbors
}

bool isProspective(Hypercube *H, Hypercube *F, int col)
{
	return abs(H->y_coords - F->y_coords ) <= 1;
}



double neighborhood_density(Hypercube *array, Hypercube *H, node *root, int position, int dimension)
{
	//initialize program
	int density = 0, countings = 0;
	int dimensions = dimension;
	
	//processing
		//initialize density with the first density/hypercube countins
		countings = H->countings;
	
			//traverse the hypercube array
			for(int k = 0; k < b; k++)
			{
				for(int j = 0; j < b; j++)
				{
				if(array[k][j] != NULL)
				{
					//check if the hypercubes are immediate
					if(	isImmediate(H, array[k][j]))
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