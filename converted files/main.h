// Preprocessor directive
#ifndef main_H
#define main_H

struct Node{
	int value;
	int begin;
	int end;
	
	struct Node *leftChild;
	struct Node *rightChild;
};

struct Tabke{
	int numRows;
	int numCols;
	char *name;
	bool hasLabel;
	Instance *instance;
	
};

struct Hypercube{
	Table *X;
	int length;
	int Wmax;
	
};

//node fnctions
Node * create_node(int value, int begin, int end); // you can use a tree with pointers instead of HashMap

//functions from dr.Gowanlock
int importDataset(char * fname, int N, double ** dataset);

//table fnctions

Table * create_table(int numRows, int numcols, Instance* instance, char* name, bool hasLabel); // this function works like a constructor

int get_num_rows(Table * X);

int get_num_cols(Table * X);


//TreeStrategy functions
int density(int i, Node parent, int col);

int * get_densities(Hypercube * H, int n, int minSplit) {
    Node root = create_node(-1, 0, H.length -1)

    # code of TreeStrategy.getDensities() goes here
}

//HySortOD functions

double * get_outlierness_score(Hypercube * H, int * W, int m);

double score(int density);

double * hysortod_score(Table * X, int b, int minSplit) {
   double l = 1 / (double) b;
   m = get_num_rows(X);

   Hypercube * H = get_sorted_hypercubes(X);
   int * W = get_densities(H, minSplit);
   double * scores = get_outlierness_score(H, W, m)

   return scores
}

//Idesity strategy functions
typedef struct IdensityStrategy{
	IdensityStrategy buildIndex(Hypercube *H);
	int *getDensities();
	double getMaxDensity();
	
};


//Instance fnctions

struct Instance{
	int id;
	int label;
	bool hasLabel;
	double *values;
};

   Instance *new_Instance( int id, double *values, int label);

   int getId(Instance *self);

   double *getValues(Instance *self);

   double getAt(int j);
   
   void setAt(int j, double value);
   
   int getLabel(Instance *self);
   
   bool hasLabel(Instance *self);
   
   int getNumDimensions(Instance *self);


	//naiveStrategy functions


	IdensityStrategy buildIndex(Hypercube *H);

	int *getDensities(Hypercube *H);




#endif  // end main_H