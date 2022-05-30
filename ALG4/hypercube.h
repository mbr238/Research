#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#include "ArrayLists.h"
const int b = 5;


//data structure
typedef struct Hypercube{
	int x_coords;
	int y_coords;
	double array[15][15];
	int countings;
}Hypercube;



void create_Hypercubes(double *values, const double length, Hypercube *array[][b])
{
	//initialize variables
		//create a new hypercube based off of values
		Hypercube *newCube = malloc(sizeof(Hypercube));
		double correctValOne = values[0], correctValTwo = values[1];
		newCube->countings = 0;
		
	//processing	
		//check if the dataset we are working with is not negative numbers
		if(values[0] > 0 && values[1] > 0)
		{
		//check if the values are above the allowed limit
		if(correctValOne > 5)
			{
				//adjust the points within the domain
				correctValOne = values[0] * length / 20;			
			}
			
			if( correctValTwo > 5)
				{	
					correctValTwo = values[1] * length / 20;
				}
			
			//check to see if hypercube is uninitialized aka equal to null
			if(array[(int)floor(correctValOne)][(int)floor(correctValTwo)] == NULL)
				{
				//add the values to the hypercube
				newCube->x_coords = correctValOne;
				newCube->y_coords = correctValTwo;
				newCube->countings++;
				
				//throw cube in array list
				array[(int)floor(newCube->x_coords)][(int)floor(newCube->y_coords)] = newCube;
				
				}
			//otherwise hypercube initialized
			else
				{
				//store the new data point within the hypercube array for each instance
				array[(int)floor(correctValOne)][(int)floor(correctValTwo)]->array[(int)floor(correctValOne)][(int)floor(correctValTwo)] = values[0];
				array[(int)floor(correctValOne)][(int)floor(correctValTwo)]->array[(int)floor(correctValOne)][(int)floor(correctValTwo+1)] = values[1];	
				array[(int)floor(correctValOne)][(int)floor(correctValTwo)]->countings++;
				free(newCube);
				}
		}
	//void function
	
}
	

int importDataset(char * fname, int N, double ** dataset)
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
        double tmp;
        sscanf(field,"%lf",&tmp);
        dataset[rowCnt][colCnt]=tmp;

        
        while (field) {
          colCnt++;
          field = strtok(NULL, ",");
          
          if (field!=NULL)
          {
          double tmp;
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