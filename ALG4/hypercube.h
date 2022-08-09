#ifndef HYPERCUBE_H
#define HYPERCUBE_H

//header files
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "params.h"
#include <stdbool.h>
#include <stdint.h>


//data structure
typedef struct Hypercube{
	int coords[DIM];
	int countings;
	
}Hypercube;


bool compare( int *coordsOne, int *coordsTwo)
{
	int coordOne, coordTwo;
	for(int i = 0; i < DIM - 1; i++)
	{
		coordOne += coordsOne[i];
		coordTwo += coordsTwo[i];
		
	}
	
	if(coordOne < coordTwo)
	{
		return true;
	}
	else
	{
		return false;
	}
}
		
		
		
uint64_t getLinearID(unsigned int * indexes, unsigned int * dimLen, unsigned int nDimensions) {
    uint64_t offset = 0;
	uint64_t multiplier = 1;
	for (int i = 0; i<nDimensions; i++){
  	offset += (uint64_t)indexes[i] * multiplier;
  	multiplier *= dimLen[i];
	}
	
	return offset;
}

int create_Hypercubes(DTYPE **dataset, Hypercube **array, int b, int N)
{
	//initialize variables
		//create a new hypercube based off of values
		uint64_t initVal = 0;
		unsigned int tempVals[DIM - 1];
        unsigned int dim[DIM - 1];
		double length = 1.0/b;
		int cubes = 0;
		for(int i = 0; i < DIM - 1; i++)
		{
			dim[i] = b;
		}
		
		
	//processing	
		for(int i = 0; i < N; i++)
			{		
				for(int k = 0; k < DIM - 1; k++)
				{
				if( dataset[i][k] < 0 )
				{
					tempVals[k] = (int)(abs(floor(dataset[i][k] / length)));
				}
				else
				{
				tempVals[k] = (int)(floor(dataset[i][k] / length));	
				}				
				}	
				
		//check if the dataset we are working with is not negative numbers			
			initVal = getLinearID( tempVals, dim, DIM - 1); // get loc of cube
			
			//check to see if hypercube is uninitialized aka equal to null
			if(array[initVal] == NULL)
				{
				Hypercube *newCube = malloc(sizeof(Hypercube));
				newCube->countings = 1; //set to 1 for having one value within the cube		
				
				//add the values to the hypercube
				for( int i = 0; i < DIM - 1; i++)
				{
					newCube->coords[i] = tempVals[i]; 
				}
				cubes++;
				
				//throw cube in array list
				array[initVal] = newCube;
				}
			//otherwise hypercube initialized
			else
				{
				//store the new data point within the hypercube array for each instance
				array[initVal]->countings++;	
				
				}
			}

					
	return cubes;
	
}
	

int importDataset(char * fname, int N, DTYPE ** dataset)
{

    FILE *fp = fopen(fname, "r");

    if (!fp) {
        printf("Unable to open file\n");
        return(1);
    }

    char buf[4096];
    int rowCnt = 0;
    int colCnt = 0;
    while (fgets(buf, 4096, fp) && rowCnt<N) {
        colCnt = 0;

        char *field = strtok(buf, ",");
        DTYPE tmp;
        sscanf(field,"%lf",&tmp);
        dataset[rowCnt][colCnt]=tmp;

        
        while (field) {
          colCnt++;
          field = strtok(NULL, ",");
          
          if (field!=NULL)
          {
          DTYPE tmp;
          sscanf(field,"%lf",&tmp);
          dataset[rowCnt][colCnt]=tmp;
          }   

        }
        rowCnt++;
    }

    fclose(fp);
    return 0;


}
#endif