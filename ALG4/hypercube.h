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
#include <time.h>
#include <omp.h>


//data structure
typedef struct Hypercube{
	int coords[DIM];
	int countings;
	
}Hypercube;

bool similarCube(Hypercube *F, Hypercube *H)
{
	for(int i = 0; i < DIM; i++)
	{
		if(abs(H->coords[i] - F->coords[i]) > 0)
		{
			return false;
		}	
	}
	return true;
}


bool compare( int *coordsOne, int *coordsTwo)
{
	int coordOne = 0, coordTwo = 0;
	for(int i = 0; i < DIM - 1; i++)
	{
		coordOne += coordsOne[i];
		coordTwo += coordsTwo[i];
		
	}
	
	if(coordOne == coordTwo)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void combineCubes(Hypercube **array,  Hypercube **wholeList, int N, int cubes)
{
	//initialize variables
	omp_set_num_threads(NTHREADS);
	int countings = 0;
	
	//processing
	#pragma omp parallel
	{
		#pragma omp for
		for(int index = 0; index < cubes; index++)
		{
			countings = 0;
			
			for(int i = 0; i < N; i++)
			{
				if(compare(array[index]->coords, wholeList[i]->coords))
				{
					countings++;
				}
			}
		array[index]->countings = countings;
		
		}
		
	}
	//return nothing void
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

int create_Hypercubes(DTYPE **dataset, int b, int N, Hypercube **array, Hypercube **wholeList)
{
	//initialize variables
		//create a new hypercube based off of values
		uint64_t initVal = 0;
		unsigned int tempVals[DIM];
        unsigned int dim[DIM];
		double length = 1.0/b;
		int cubes = 0, index = 0;	
		
		for(int k = 0; k < N; k++)
		{
			array[k] = NULL;
			wholeList[k] = NULL;
		}
		
		for(int i = 0; i < DIM; i++)
		{
			dim[i] = b;
		}
			
		
	//processing	
		for(int i = 0; i < N; i++)
			{		
				for(int k = 0; k < DIM; k++)
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
				
			Hypercube *newCube = malloc(sizeof(Hypercube*));

				
			//add the values to the hypercube
				for( int i = 0; i < DIM; i++)
				{
					newCube->coords[i] = tempVals[i]; 
				}
			newCube->countings = 0; 	
			
		//check if the dataset we are working with is not negative numbers			
			initVal = getLinearID( tempVals, dim, DIM); // get loc of cube
					
			wholeList[index] = newCube;	
			index++;
			
			//could sort list later using a paralllel program pulling out unique cubes
			
			//check to see if hypercube is uninitialized aka equal to null
			if(array[initVal] == NULL)
				{
				cubes++;
				
				//throw cube in array list
				array[initVal] = newCube;
				
				}
			
			}
			
			
	return cubes;
}

//create two arrays, one array is sequential putting linID/coords in a cube into an array
// and the other array is each unique cube that will be paralleled to find similar cubes in the first array

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