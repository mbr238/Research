//header files
#include "hysortod.h"
#include "params.h"

//global constants


//prototypes

DTYPE getMax(DTYPE **dataset, int N);

DTYPE getMin(DTYPE **dataset, int N);


int main(int argc, char **argv)
{
	//initialize variables/datasets
	int i = 0, N, bins = 5;
	sscanf(argv[1],"%d",&N);	//number of lines in text
	DTYPE **dataset;
	char inputFname[500];
    strcpy(inputFname,argv[2]);	// the file name	
	//allocate memory for dataset
	dataset=(DTYPE**)malloc(sizeof(DTYPE*)*N);
	for (int i=0; i<N; i++)
	{
	dataset[i]=(DTYPE*)malloc(sizeof(DTYPE)*DIM);
	}
	
	//import the data set
	importDataset(inputFname, N, dataset);		
	
	int arrSize = N;
	DTYPE *outlierArray = (DTYPE*)malloc(sizeof(DTYPE*)*arrSize);

	Hypercube **array = (Hypercube**)malloc(sizeof(Hypercube)*N);
	Hypercube **sortArray = (Hypercube**)malloc(sizeof(Hypercube)*N);	
	
	
	//initialize array to null initially
 	for(i = 0; i < N; i++)
	{
	array[i] = NULL;
	}
		
	//min = getMin(dataset, N);

	//start the timer
	clock_t start, end;
	DTYPE cpu_time_used;
	start = clock();
	
	//perform outlier algorithm
	HYsortOD(outlierArray, dataset, array, sortArray, N, bins);
	
	//end timer
	end = clock();
	cpu_time_used = ((DTYPE) (end - start)) / CLOCKS_PER_SEC;
	//print how long it took to calculate outliers
	
	//iterate through the outlier array
	for(int i = 0; i < arrSize; i++)
	{
			//if the outlier array spot is not equal to 0( aka not initialized)
			while(sortArray[i] != NULL)
			{
			//print out the outlier score to that hypercube
			printf("%lf\n",outlierArray[i]);
			i++;
			}
			

	}
	  //free dataset
	  for (int i=0; i<N; i++)
	  {
		free(dataset[i]);
	  }

	  free(dataset);	
	  free(outlierArray);
	  free(sortArray);
	  
	printf("Time used : %f\n", cpu_time_used);		
	printf("End program!");
	return 0;
}

//implementation of prototypes
DTYPE getMax(DTYPE **dataset, int N)
{
	//initialize variables
	DTYPE max = 0.0;
	
	//processing
		//assume first one is max
		max = dataset[0][0];
		
		//loop through dataset to find max
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < DIM; j++)
			{
				//check if the value is max value
				if(dataset[i][j] > max)
				{
					max = dataset[i][j];
				}
			}
		}
	
	//return the max
	return max;
}

DTYPE getMin(DTYPE **dataset, int N)
{
	//initialize variables
	DTYPE min = 0.0;
	
	//processing
		//assume first one is min
		min = dataset[0][0];
		
		//loop through dataset to find min
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < DIM; j++)
			{
				//check if the value is min value
				if(dataset[i][j] > 0 && dataset[i][j] < min)
				{
					min = dataset[i][j];
				}
			}
		}
	
	//return the max
	return min;	
}