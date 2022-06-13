//header files
#include "hysortod.h"
#include "params.h"

//global constants


//prototypes

DTYPE getMax(DTYPE **dataset, int N);

DTYPE getMin(DTYPE **dataset, int N);


int main()
{
	//initialize variables/datasets
	int bins = 5;
    int i = 0;
	int N = 5159738, arrSize = N;
	DTYPE *outlierArray = (DTYPE*)malloc(sizeof(DTYPE*)*pow(bins - 1,DIM));
	DTYPE **dataset;
    char inputFname[500] = "file.txt";	
	//DTYPE max = 0, min = 0;
	Hypercube **array = malloc(sizeof(Hypercube*)*arrSize);

	
	//initialize array to null initially
 	for(i = 0; i <= N; i++)
	{
	array[i] = NULL;
	}
	
	//allocate memory for dataset
		dataset=(DTYPE**)malloc(sizeof(DTYPE*)*N);
		for (int i=0; i<N; i++)
		{
		dataset[i]=(DTYPE*)malloc(sizeof(DTYPE)*DIM);
		}	
		
		
		//set the outlier array originally to 0s 
		for(int i = 0; i <= pow(bins - 1,DIM); i++)
		{
		outlierArray[i] = 0.0;
		}
		
	//import the data set
	importDataset(inputFname, N, dataset);	
	
	//get the max and min of the dataset
	//max = getMax(dataset, N);
		
	//min = getMin(dataset, N);

	
	//start the timer
	clock_t start, end;
	DTYPE cpu_time_used;
	start = clock();
				
	//perform outlier algorithm
	HYsortOD(bins, outlierArray, dataset, array, N);
	
	//end timer
	end = clock();
	cpu_time_used = ((DTYPE) (end - start)) / CLOCKS_PER_SEC;
	//print how long it took to calculate outliers
	printf("Time used : %f\n", cpu_time_used);		
		


	
	//iterate through the outlier array
	for(int i = 0; i <= pow(bins - 1, DIM); i++)
	{
			//if the outlier array spot is not equal to 0( aka not initialized)
			if(array[i] != NULL)
			{
			//print out the outlier score to that hypercube
			printf(" position: [%d]: Outlier Score: %lf\n",i,outlierArray[i]);
			}

	}
	
	
	
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
		//assume first one is max
		min = dataset[0][0];
		
		//loop through dataset to find max
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < DIM; j++)
			{
				//check if the value is max value
				if(dataset[i][j] > 0 && dataset[i][j] < min)
				{
					min = dataset[i][j];
				}
			}
		}
	
	//return the max
	return min;	
}