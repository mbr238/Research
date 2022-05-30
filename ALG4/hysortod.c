#include "hysortod.h"



void HYsortOD(int bins, int minSplit, double outlierArray[][b], double **dataset, double length);

double myScore(double density, double densityMax);

double neighborhood_density(Hypercube* array[][b], Hypercube *H);
												//fix with binary tree root
void construct( Hypercube *array, int minSplit, Hypercube* root, int constant);

double max(double W[][b], int b);

int main()
{
	//initialize variables/datasets
	int bins = 5;
	int minSplit = 100;
	double outlierArray[b][b];
	double **dataset;
    char inputFname[500] = "file.txt";	

	
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
		
	//perform outlier algorithm
	HYsortOD(bins, minSplit, outlierArray, dataset, length);
	
	//iterate through the outlier array
	for(int i = 0; i < b;i++)
	{
		for(int j = 0; j < b; j++)
		{
			//if the outlier array spot is not equal to 0( aka not initialized)
			if(outlierArray[i][j] != 0)
			{
			//print out the outlier score to that hypercube
			printf(" position: [%d,%d]: Outlier Score: %lf\n",i,j,outlierArray[i][j]);
			//goto next row once j is 4
			if(j == 4)
			{
				printf("Next row\n");
			}
			}
		}
	}
	
	

	
	printf("Complete");
	return 0;
}