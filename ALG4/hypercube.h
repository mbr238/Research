#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "params.h"

//#include "ArrayLists.h"
const int b = 5;
const int N = 5159746; // how long the file is for dataset importing

//data structure
typedef struct Hypercube{
	int coords[DIM];
	int countings;
	
}Hypercube;



void create_Hypercubes(DTYPE *values, const DTYPE length, Hypercube *array[][b], int b)
{
	//initialize variables
		//create a new hypercube based off of values
		Hypercube *newCube = malloc(sizeof(Hypercube));
		DTYPE correctValOne = values[0], correctValTwo = values[1];
		newCube->countings = 0;
		
	//processing	
		//check if the dataset we are working with is not negative numbers
		if(values[0] > 0 && values[1] > 0)
		{
		//check if the values are above the allowed limit
		if(correctValOne > b)
			{
				//adjust the points within the domain
				correctValOne = values[0] * length / 20;			
			}
			
			if( correctValTwo > b)
				{	
					correctValTwo = values[1] * length / 20;
				}
			
			//check to see if hypercube is uninitialized aka equal to null
			if(array[(int)floor(correctValOne)][(int)floor(correctValTwo)] == NULL)
				{
				//add the values to the hypercube
				newCube->coords[0] = correctValOne;
				newCube->coords[1] = correctValTwo;
				newCube->countings++;
				
				//throw cube in array list
				array[(int)floor(newCube->coords[0])][(int)floor(newCube->coords[1])] = newCube;
				
				}
			//otherwise hypercube initialized
			else
				{
				//store the new data point within the hypercube array for each instance
				array[(int)floor(correctValOne)][(int)floor(correctValTwo)]->countings++;
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