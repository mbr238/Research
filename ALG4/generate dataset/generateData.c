//header files
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>  // for srand
#include "StandardConstants.h"
#include "File_Output_Utility.h"

//global constants
	

//prototypes
double randfrom(double min, double max) ;
	
//main function
int main()
{
	//initialize variables
	double max = 400.0, min = 0.0;
	int DIM = 10, N = 5000000;
	
       // initialize random seed
       srand( time( NULL ) );	
	   
	//generate dataset
	openOutputFile("test.txt");
	
	double current = randfrom(min, max);
	
	
	for(int i = 0; i < N; i++)
	{
		for(int k = 0; k < DIM; k++)
		{
			writeDoubleToFile(current, 6);
			if(k != DIM - 1)
			{
			writeCharacterToFile(COMMA);
			}
			current = randfrom(min, max);
			
			if( k == DIM - 1)
			{
				writeEndlineToFile();
			}
		}
		
	}
	closeOutputFile("test.txt");
	
	
	printf("end program");
	return 0;
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}