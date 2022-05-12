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
#include "main.h"
#include <math.h>
#include <stdbool.h>

//constants
#define STD_STR_LEN 64
#define DIM 2
const int N = 500;

//function prototypes
int importDataset(char * fname, int N, double ** dataset);

int main( int argc, char* argv[] )
{
	//initialize parameters
	char fileName[ STD_STR_LEN ];
	int b = 0, minSplit = 0;
	int reportOutput = 0;
	double ** dataset;
	
	//make sure there are 5 arguments
  if (argc != 6) {
    printf(" Parameters: dataset_path label_column num_bins min_split report_output\n");
	printf(" dataset_path is string to dataset path.\n");
	printf(" Assume no label mark -1\n");
	printf(" num_bins must be greater than 1.\n");
	printf(" min_split = 0 enables naive search.\n");
	printf(" report_output is 0 or 1\n");
    exit(0);
  }	
	
	//parameters are as follows: dataset_path label_column num_bins min_split report_output
	strcpy(fileName,argv[1]);
    // assume no label 
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
	IDensityStrategy *strategy = (IDensityStrategy *)malloc(sizeof(IDensityStrategy));
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

    int ret=importDataset(fileName, N, dataset);
	
	//run algorithm and compute runtime
	clock_t begin = clock();
	HySortOD hsod = malloc((struct Hypercube*)malloc(sizeof(*hsod)));
	double yPred = hysortod_score(ret, b, minSplit);
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("runtime: %.8f", time);
		
		
	//calculate the AUC score if possible
		int *yTrue = getLabels(ret);
		double auc = AUC_measure(yTrue, yPred );
		printf("rocauc: %.8f", auc);
	
	//report outlierness score for each instance
	if(reportOutput == 1)
	{

			int *yTrue = getLabels(ret);
			for(int i = 0; i < yTrue; i++){
				printf("%d,%.4f", yTrue[i], yPred[i]);
			}
		
	}

 //return program success
 return 0;
}
	//implementation of functions
			
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

	
		//node functions
		struct Node *root = NULL;
		
		Node * create_node(int value, int begin, int end) // tree with pointers 
		{
			//initialize variables
			struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
			newNode->value = value;
			struct Node *current;
			struct Node *parent;
			
			newNode->leftChild = NULL;
			newNode->rightChild = NULL;
			
			//processing
				//check to see if tree is empty
				if(root == NULL)
				{
					root = newNode;
				}
				else
				{
					current = root;
					parent = NULL;
					
					while(1)
					{
						parent = current;
						
						//goto left of tree
						if(value < parent->value)
						{
							current = current->leftChild;
							
							//insert to the left
							if(current == NULL)
							{
								parent->leftChild = newNode;
								return root;
							}
						}
						else
						{
							current = current->rightChild;
							
							//insert to right
							if(current == NULL)
							{
								parent->rightChild = newNode;
								return root;
							}
							
						}
						
					}
				}
			
			//return the node
			return root;
		}


		int get_num_rows(int * X)
		{
			//initialize program
			int numRows;
			
			//processing
			numRows = X->numRows;
			
			//return number of rows
			return numRows;
		}

		int get_num_cols(Table * X)
		{
			//initialize program
			int numCols;
			
			//processing
			numCols = X->numCols;
			
			//return number of rows
			return numCols;
		}
		

	double * get_outlierness_score(Hypercube * H, int * W, int m)
	{
		//initialize program
		double *O = double *m;
		
		//processing
		
		int i = 0;
		for(Hypercube h: H)
		{
			for(Instance x : getInstances(h))
			{
				O[getID(x)] = score(W[i]);
				
			}
			i++;
			
		}
		
		return O;
		//return outlier score
		
	}

	double score(int density)
	{
		//return the score
		return 1 - (density / getMaxDensity(strategy));;	
	}

	double * hysortod_score(int * X, int b, int minSplit) {
	   double l = 1 / (double) b;
	   int *m = get_num_rows(X);

	   Hypercube * H = get_sorted_hypercubes(X);
	   int * W = get_densities(H, l, minSplit);
	   double * scores = get_outlierness_score(H, W, m);

	   return scores;
	}
   Instance *new_Instance( int id, double *values, int label)
   {
	   //initialize program
	   Instance *newNode = (struct Instance*)malloc(sizeof(Instance));
	   newNode->id = id;
	   newNode->label = label;
	   int i = 0;
	   
	   //processing
	   for(i = 0; values[i] != NULL; i++)
	   {
		   //do nothing get size of value
		   
	   }
	   
	   for(int k = 0; k < i; k++)
	   {
		   newNode->values[k] = values[k];
	   }
	   
	   //return the instance
	   return newNode;
   }
   
   int getId(Instance *self)
   {
	   return self->id;
   }

   double *getValues(Instance *self)
   {
	   return self->values;
   }

   double getAt(Instance *self, int j)
   {
	   return self->values[j];
   }
   
   void setAt(Instance *self, int j, double value)
   {
	   self->values[j] = value;
   }
   
   int getLabel(Instance *self)
   {
	   return self->label;
   }
   
   bool hasLabel(Instance *self)
   {
	   return self->hasLabel;
   }
   
   int getNumDimensions(Instance *self)
   {
	   //initialize program
	   int length = 0;
	   double * values = self->values;
	   int colIndex = 0, rowIndex = 0;
	   
	   //processing
		//loop through the values of the instance
	    for(rowIndex = 0; values[rowIndex][colIndex] != NULL; rowIndex++)
		{
			for(colIndex = 0; values[rowIndex][colIndex] != NULL; colIndex++)
			{
				//do nothing
				
			}
			length++; // find how many rows there are
		}
	   //return length
	   return length;
   }
   
   
   	//naiveStrategy functions


	IdensityStrategy buildIndex(Hypercube *H)
	{
		//initialize pgoram
		IdensityStrategy *newNode = (struct Hypercube*)malloc(sizeof(H));
		
		//processing
		newNode->Wmax = 0;
		
		//return the hypercube
		return newNode;
	}

	int *getDensities(Hypercube *H)
	{
		//initialize program
		int n = sizeof(H);
		int *W = malloc(sizeof(Hypercube));
		
		//processing
		for(int i = 0; i < n; i++)
		{
			W[i] = getDensity(H[i]);
			
			for(int k = i - 1; k >=0; k--)
			{
				if(!isProspective(H[i],H[k],0))
				{
					break;
				}
				if(isImmdiate(H[i],H[k]))
				{
					W[i] += getDensity(H[k]);
				}
			
			}
			for (int k = i + 1; k < n; k++) {
				if (!isProspective(H[i], H[k], 0))
					break;
				if (isImmediate(H[i], H[k]))
					W[i] += getDensity(H[k]);
			}
			
			int Wmax = max(Wmax,W[i]);
			
		}
		
		//return the densities
		return W;
		
	}
	
	//Auc measure function
double AUC_measure(int * truth, double * probability)
	{
		//initialize program
		int truthLength = 0, probabilityLength = 0;
		
		//processing
			//calculate length of truth
			while(!(truth[truthLength+1] != 0) || !(truth[truthLength+1] != 1) )
			{
				truthLength++;
			}
			

			//calculate length of  probability
			while(!(probability[probabilityLength+1] != 0) || !(probability[probabilityLength+1] != 1) )
			{
				probabilityLength++;
			}
			
			printf("%d,%d,",truthLength,probabilityLength);
			//check if they are the same length
			if(probabilityLength != truthLength)
			{
				//exit and print error message
				printf("Vector sizes dont match");
				exit(0);
			}
			
			//otherwise continue
			double pos = 0.0;
			double neg = 0.0;
			
        for (int i = 0; i < truthLength; i++) {
            if (truth[i] == 0) {
                neg++;
            } else if (truth[i] == 1) {
                pos++;
            } else {
                printf("AUC is only for binary classification. Invalid label");
				exit(1);
            }
        }

		//get new table copies
		int *label = truth;
		double *prediction = probability;
		
		double rank[truthLength];
		for (int i = 0; i < probabilityLength; i++) {
            if (i == probabilityLength - 1 || prediction[i] != prediction[i+1]) {
                rank[i] = i + 1;
            } else {
                int j = i + 1;
                for (; j < probabilityLength && prediction[j] == prediction[i]; j++);
                double r = (i + 1 + j) / 2.0;
                for (int k = i; k < j; k++) rank[k] = r;
                i = j - 1;
            }
        }
		
		//calculate auc
		double auc = 0.0;
        for (int i = 0; i < truthLength; i++) {
            if (label[i] == 1)
                auc += rank[i];
        }

        auc = (auc - (pos * (pos+1) / 2.0)) / (pos * neg);
        return auc;
		
	}


//abstract density strategy functions

double getMaxDensity(Hypercube *self)
{
	return self->Wmax;
}

bool isImmediate(Hypercube hi, Hypercube hk)
{
	int *p = getCoords(hi);
	
	int *q = getCoords(hk);
	
	int p_size = sizeof(p)/sizeof(*p);
	
	for(int j = p_size - 1; j >= 0; j++)
	{
		if(abs(p[j] - q[j]) > 1)
		{
			return false;
		}
	}
	return true;
}


bool isProspective(Hypercube hi, Hypercube hk, int col)
{
	return (abs(getCoordAt(hi,col) - getCoordAt(hk,col)) <= 1);
}

