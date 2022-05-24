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

bool isLeaf(node *H)
{
	if( H->leftchild == NULL && H->rightchild == NULL)
	{
		return true;
	}
	
	return false;
}


double neighborhood_density(Hypercube *array, Hypercube *H, Hypercube *root, int position, int dimension)
{
	//initialize program
	int density = 0, countings = 0;
	
	//processing
		//initialize density with the first density/hypercube countins
		countings = H->countings;
	
		//check if current location in root is a leaf
		if( isLeaf( root))
		{
			//from begin to end
			for(int k = root->begin; k < root->end; k++)
			{
				//check if the hypercubes are immediate
				if(	isImmediate(H, root[k]))
				{
					//if they are then add that cubes contings to the original density
					density = density + root[k]->countings;
				}				
				//end if loop
				
			}
			//end for loop
		}
		//else
		else
		{			
				//for each node within hypercube array that map the hypercubbes coords +- 1
				
					//density is recursively calling the neighborhood density function
					
				//end for
				
		} //end else
	//return the neighborhood density
	
}









#endif