#include "hysortod.h"



void HYsortOD(int bins, int minSplit, double **outlierArray, double **dataset, double length);

double myScore(double density, double densityMax);

double neighborhood_density(Hypercube* array[][b], Hypercube *H);
												//fix with binary tree root
void construct( Hypercube *array, int minSplit, Hypercube* root, int constant);

double max(double W[][b], int b);

int main()
{
	int bins = 5;
	int minSplit = 100;
	double **outlierArray;
	double **dataset;
    char inputFname[500] = "file.txt";	

	
	//allocate memory for dataset
		dataset=(double**)malloc(sizeof(double*)*N);
		for (int i=0; i<N; i++)
		{
		dataset[i]=(double*)malloc(sizeof(double)*DIM);
		}	
	
	 //allocate memory for dataset
		outlierArray=(double**)malloc(sizeof(double*)*N);
		for (int i=0; i<N; i++)
		{
		  outlierArray[i]=(double*)malloc(sizeof(double)*DIM);
		}
	
	importDataset(inputFname, N, dataset);	
	
	
	HYsortOD(bins, minSplit, outlierArray, dataset, length);
	
	for(int i = 0; i < b;i++)
	{
		for(int j = 0; j < b; j++)
		{
			printf("%lf,%lf\n",outlierArray[i][0],outlierArray[i][1]);
			
		}
	}
	
	
	printf("Complete");
	return 0;
}