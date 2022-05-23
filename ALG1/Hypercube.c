#include "hypercube.h"


//function prototypes


int main()
{
	//initialize parameters
	double values[2];
	double length = 0.20;
	Hypercube *array[b][b];
    int N = 5159000;
    int DIM = 2;
    char inputFname[500] = "file.txt";
    double **dataset;
 
	//initialize array to null initially
 	for(int i = 0; i < b; i++)
	{
		for(int j = 0; j < b; j++)
		{
		array[i][j] = NULL;
		}
		
	}
	
    //allocate memory for dataset
    dataset=(double**)malloc(sizeof(double*)*N);
    for (int i=0; i<N; i++)
    {
      dataset[i]=(double*)malloc(sizeof(double)*DIM);
    }

	importDataset(inputFname, N, dataset);

	for(int i = 0; i < N; i++)
	{
			values[0] = dataset[i][0];
			values[1] = dataset[i][1];
			create_Hypercubes( values, length, array);	
	}	

	for(int i = 0; i < b; i++)
	{
		for(int j = 0; j < b; j++)
		{
			if(array[i][j] != NULL)
			{
			printf("%d,%d\n",array[i][j]->x_coords,array[i][j]->y_coords);	
			}
		
		
		}
		
	}

	
			
		



return 0;
}