//This is converted Java code to C

/*header files
#include "AUC.h"
#include "Table.h"
#include "TreeStrategy.h"
#include "HySoryOD.h"
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "IDensityStrategy.h"
#include <jni.h>

//constants
#define STD_STR_LEN 64
#define DIM 2

//function prototypes
int importDataset(char * fname, int N, double ** dataset);

int main( int argc, char* argv[] )
{
	//initialize parameters
	char fileName[ STD_STR_LEN ];
	int labelCol = 0, b = 0, minSplit = 0;
	int reportOutput = 0;

	
	//make sure there are 5 arguments
  if (argc != 6) {
    printf(" Parameters: dataset_path label_column num_bins min_split report_output\n");
	printf(" dataset_path is string to dataset path.\n");
	printf(" label_column = -1 means no label.\n");
	printf(" num_bins must be greater than 1.\n");
	printf(" min_split = 0 enables naive search.\n");
	printf(" report_output is 0 or 1\n");
    exit(0);
  }	
	
	//parameters are as follows: dataset_path label_column num_bins min_split report_output
	strcpy(fileName,argv[1]);
    sscanf(argv[2],"%d",&labelCol);
    sscanf(argv[3],"%d",&b);
    sscanf(argv[4],"%d",&minSplit);
    sscanf(argv[5],"%d",&reportOutput);	

	//check the parameters
	if (b <= 1) {
		printf("Number invalid for parameter bins, reason: b <= 1\n");
		exit(0);
	}
		
	if (minSplit < 0) {
		printf("Number invalid for parameter min_split, reason: min_split < 0\n");
		exit(0);			
	}	

	//instantiate the specified mapper
	IDensityStrategy *strategy = malloc(NaiveStrategy()* sizeof(*strategy));
	if( minSplit > 0) {
		strategy = TreeStrategy(minSplit);
		printf("[INFO] Using Tree-based Search");
	}
	else {
		printf("[INFO] Using naive Search");
	}

	//import the data set
	//allocate memory for dataset
    dataset=(double**)malloc(sizeof(double*)*N);
    for (int i=0; i<N; i++)
    {
      dataset[i]=(double*)malloc(sizeof(double)*DIM);
    }

    int ret=importDataset(inputFname, N, dataset);


	//read the dataset
	Table data = Table.readCSV(fileName, ",", labelCol, true);
	
	//run algorithm and compute runtime
	clock_t begin = clock();
	HySortOD hsod = malloc(HySortOD(b, strategy)* sizeof(*hsod));
	double yPred = hsod->score(dataset);
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("runtime: %.8f", time);
		
		
	//calculate the AUC score if possible
	if(dataset.hasLabel()){
		int yTrue = dataset->getLabels();
		double auc = AUC->measure(yTrue, yPred );
		printf("rocauc: %.8f", auc);
	}
	
	//report outlierness score for each instance
	if(reportOutput == 1)
	{
		if(dataset.hasLabel()){
			int yTrue = dataset->getLabels;
			for(int i = 0; i < yTrue; i++){
				printf("%d,%.4f", yTrue[i], yPred[i]);
			}
		else{
			for(int i=0; i < yPred; i++)
			{
				printf("%.4f",yPred[i]);
			}
		}
		
		}
	}

 //return program success
 return 0;
}
	
	
	
	
	
	
