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
	double countings;
	
}Hypercube;

uint64_t getLinearID(unsigned int * indexes, unsigned int * dimLen, unsigned int nDimensions) {
    uint64_t offset = 0;
	uint64_t multiplier = 1;
	for (int i = 0; i<nDimensions; i++){
  	offset += (uint64_t)indexes[i] * multiplier;
  	multiplier *= dimLen[i];
	}
	
	return offset;
}



void create_Hypercubes(DTYPE *values, Hypercube **array, int b)
{
	//initialize variables
		//create a new hypercube based off of values
		Hypercube *newCube = malloc(sizeof(Hypercube));
		newCube->countings = 0;
		bool initFlag = true;
		int tempVal = 0, initVal = 0;
		unsigned int tempVals[DIM];
        unsigned int dim[DIM];
		
		for(int i = 0; i < DIM; i++)
		{
			dim[i] = b;
		}
		
	//processing	
		//check if the dataset we are working with is not negative numbers
		for(int i = 0; i < DIM; i++)
		{
			if(values[i] < 0.0)
			{
				initFlag = false;
				free(newCube);
			}
		}
			if(initFlag)
			{
			
			//get the spot that is going to be initialized if not already
			for(int i = 0; i < DIM; i++)
			{		
			if(values[i] > 4)
			{
			tempVal = (int)(values[i] / 100.0);
			}
			else
			{
			tempVal = (int) values[i];
			}
			tempVals[i] = tempVal;
			}
			
			initVal = getLinearID( tempVals, dim, DIM);
			
			//check to see if hypercube is uninitialized aka equal to null
			if(array[initVal] == NULL)
				{
				//add the values to the hypercube
				for( int i = 0; i < DIM; i++)
				{
					newCube->coords[i] = tempVals[i]; 
					
				}
				newCube->countings++;
				
				//throw cube in array list
				array[initVal] = newCube;
				
				}
			//otherwise hypercube initialized
			else
				{
				//store the new data point within the hypercube array for each instance
				array[initVal]->countings++;
				free(newCube);
				
				}
			}
	//void function
	
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