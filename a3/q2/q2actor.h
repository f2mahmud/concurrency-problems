#include <uActor.h>

struct MatrixMessage : public uActor::Message { 
	int **X;
	int **Y;
	int **Z;
	unsigned int xcyr, rowNumber;
	int yc;
	MatrixMessage( int *X[], int *Z[], unsigned int rowNumber, unsigned int xcyr, int *Y[], int yc );
};

_Actor MatrixMultiply {
	
	Allocation receive( Message & msg );
	
};