#ifndef BINARY_H
#define BINARY_H

//header files
#include "hypercube.h"
#include <stdbool.h>


typedef struct node{
	
}node;

    int i;

// If the hypercube is NULL
bool sort(Hypercube **array, int N) {
	for (i = 0; i < N; i++) {
		int low = 0;
		int high = 0;
		int node;
		while (low <= high ) {
            int mid = (low + high) / 2;
			if (Hypercube **array >= Key) {
				low = mid + 1;
			}
			else if (Hypercube **array <= Key) {
				high = mid - 1;
			}
		}
	}
	
}







#endif
