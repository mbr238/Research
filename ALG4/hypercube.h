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
	int countings;
	int coords[DIM];
	int loc;
	uint64_t location;
}Hypercube;


//prototypes
int getUniques(Hypercube **array, Hypercube **wholeList, int N);


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

			Hypercube *newCube = (Hypercube*)malloc(sizeof(Hypercube*));

			//add the values to the hypercube
				for( int i = 0; i < DIM; i++)
				{
					newCube->coords[i] = tempVals[i]; 
				}
			newCube->countings = 0;

		//check if the dataset we are working with is not negative numbers
			initVal = getLinearID( tempVals, dim, DIM); // get loc of cube

			newCube.location = initVal;
			wholeList[index] = newCube;
			index++;

			//could sort list later using a parallel program pulling out unique cubes

			//check to see if hypercube is uninitialized aka equal to null

			/*if(array[initVal] == NULL)
				{
				cubes++;

				//throw cube in array list
				array[initVal] = newCube;

				}*/

			free(newCube);
			}
	cubes = getUniques(array,wholeList,N);
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

bool isInArray(uint64_t loc, Hypercube **array, int N)
{
  int index = 0;

  for(index = 0; index < N; index++)
   {
   if(loc == array[index]->location)
   {
    return true;
   }
   }
  return false;
}



int getUniques(Hypercube ** array, Hypercube ** wholeList, int N) {
    int index = 0, arrayIndex = 1;

    array[arrayIndex] = wholeList[index];

   for(index = 0; index < N; index++)
   {
    if(!isInArray(wholeList[index]->location,array,arrayIndex))
	{
	array[arrayIndex] = wholeList[index];
	arrayIndex++;
	}
   }

	return arrayIndex;
}

#endif
