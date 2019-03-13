#include <uCobegin.h>
#include <iostream>

#if defined(ACTOR)
#include "q2actor.h"

#elif defined(TASK)
#include "q2task.h"

unsigned int MatrixMultiplier::xr;
unsigned int MatrixMultiplier::xcyr;
unsigned int MatrixMultiplier::yc;
int** MatrixMultiplier::X;
int** MatrixMultiplier::Y;
int** MatrixMultiplier::Z;

#endif

using namespace std;

int multiply(int *X, unsigned int xcyr, int *Y[], int yc){
	int result = 0;
	for(int unsigned i = 0; i < xcyr ; i++ ){
		result += X[i] * Y[i][yc];
	}
	return result;
}


void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc ){
	
#if defined(CFOR)
	
	COFOR(i, 0, xr,	
		for(unsigned int j = 0; j < yc ; j++){
			Z[i][j] = multiply(X[i],xc,Y,j);
		}
	);

#elif defined(ACTOR)

	uActorStart();
	for(unsigned int i = 0; i < xr; i++ ){
		*(new MatrixMultiply()) | * new MatrixMessage(X,Z,i,xc,Y,yc);	
	}
	uActor::stop();
	
#elif defined(TASK)
	
	MatrixMultiplier::xr = xr;
	MatrixMultiplier::xcyr = xc;
	MatrixMultiplier::yc = yc;
	
	MatrixMultiplier::X = X;
	MatrixMultiplier::Y = Y;
	MatrixMultiplier::Z = Z;
	
	int half = floor( xr / 2 );
	MatrixMultiplier m(half, half - 1);
	
#endif
	
}
