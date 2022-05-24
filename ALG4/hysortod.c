#include "hysortod.h"



void HYsortOD(int bins, int minSplit, double **outlierArray, double **dataset, double length);

double myScore(double density, double densityMax);

															//fix with binary tree root
double neighborhood_density(Hypercube *array, int countings, Hypercube *root, int position, int dimension);

												//fix with binary tree root
void construct( Hypercube *array, int minSplit, Hypercube* root, int constant);


double max(double W[][b], int b);


int main()
{
	int bins = 5;
	int minSplit = 5;
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
	
	
	printf("Complete");
	return 0;
}