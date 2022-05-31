//header files
#include "hysortod.h"


//global constants


//prototypes
void HYsortOD(int bins, int minSplit, double outlierArray[][b], double **dataset, double length);

double myScore(double density, double densityMax);

double neighborhood_density(Hypercube* array[][b], Hypercube *H);
												//fix with binary tree root
void construct( Hypercube *array, int minSplit, Hypercube* root, int constant);

double max(double W[][b], int b);

double getMax(double **dataset);

double getMin(double **dataset);


int main()
{
	//initialize variables/datasets
	int bins = 5;
	int minSplit = 100;
	double outlierArray[b][b];
	double **dataset;
    char inputFname[500] = "file.txt";	
	double length = 1.0/b;
	double max = 0, min = 0;
	
	//allocate memory for dataset
		dataset=(double**)malloc(sizeof(double*)*N);
		for (int i=0; i<N; i++)
		{
		dataset[i]=(double*)malloc(sizeof(double)*DIM);
		}	
		
		
		//set the outlier array originally to 0s 
		for(int i = 0; i < b; i++)
		{
			for(int j = 0; j < b; j++)
			{
				outlierArray[i][j] = 0.0;
			}
		}
		
	//import the data set
	importDataset(inputFname, N, dataset);	
	
	//get the max and min of the dataset
	max = getMax(dataset);
		
	min = getMin(dataset);

	
	//start the timer
	clock_t start, end;
	double cpu_time_used;
	start = clock();
				
	//perform outlier algorithm
	HYsortOD(bins, minSplit, outlierArray, dataset, length);
	
	//end timer
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//print how long it took to calculate outliers
	printf("Time used : %f\n", cpu_time_used);		
		


	
	//iterate through the outlier array
	for(int i = 0; i < b;i++)
	{
		for(int j = 0; j < b; j++)
		{
			//if the outlier array spot is not equal to 0( aka not initialized)
			if(outlierArray[i][j] != 0.0)
			{
			//print out the outlier score to that hypercube
			printf(" position: [%d,%d]: Outlier Score: %lf\n",i,j,outlierArray[i][j]);
			}
			//goto next row once j is 4			
			if(j == 4)
			{
				printf("Next row\n");
			}
		}
	}
	
	printf("End program!");
	return 0;
}

//implementation of prototypes
double getMax(double **dataset)
{
	//initialize variables
	double max = 0.0;
	
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

double getMin(double **dataset)
{
	//initialize variables
	double min = 0.0;
	
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