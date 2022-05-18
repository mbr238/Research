#ifndef HYPERCUBE_H
#define HYPERCUBE_H
#define b 5
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Hypercube{
	int x_coords;
	int y_coords;
	double array[b][b];

}Hypercube;


int getXCoords(Hypercube *H)
{
	return H->x_coords;
}

int getYCoords(Hypercube *H)
{
	return H->y_coords;
}

int compare_Cubes(Hypercube *H, Hypercube *C)
{
	//initialize variables
	int xCoordsFirstCube = 0, yCoordsFirstCube = 0;
	int xCoordsSecondCube = 0, yCoordsSecondCube = 0;
	
	//processing
		//get the coordinants of both hypercubes
		xCoordsFirstCube = getXCoords( H );
		yCoordsFirstCube = getYCoords( H );
		xCoordsSecondCube = getXCoords( C );
		yCoordsSecondCube = getYCoords( C );
		
		//see if the second cube is within 1  distance of the second cube
		if( xCoordsFirstCube - xCoordsSecondCube != 0)
		{
			return (xCoordsFirstCube - xCoordsSecondCube);
		}
		if( yCoordsFirstCube - yCoordsSecondCube != 0)
		{
			return (yCoordsFirstCube - yCoordsSecondCube);
		}
	
	
	//return that they are not zero
	return 0;
}



void create_Hypercubes(double *values, const double length, Hypercube *array[][b])
{
	//initialize variables
		//create a new hypercube based off of values
		Hypercube *newCube = malloc(sizeof(Hypercube));
		double correctValOne = 0, correctValTwo = 0;
		
	//processing
		//check if the values are above the allowed limit
		if(values[0] > 5 && values[1] > 5)
		{
			//adjust the points within the domain
			correctValOne = values[0] * length / 20;
			
			correctValTwo = values[1] * length / 20;
		}
		
		
	newCube->array[(int)correctValOne][(int)correctValTwo] = correctValOne;
	newCube->array[(int)correctValOne][(int)correctValTwo + 1] = correctValTwo;		
		
		//add the values to the hypercube
		newCube->x_coords = correctValOne;
		newCube->y_coords = correctValTwo;
		
		//throw cube in array list
		array[(int)floor(newCube->x_coords)][(int)floor(newCube->y_coords)] = newCube;
		
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