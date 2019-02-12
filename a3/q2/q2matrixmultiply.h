#include <uCobegin.h>
#include <iostream>

using namespace std;


void multiply(int *Z[], int *X[], unsigned int xr, unsigned int xcyr, int *Y[], unsigned int yc){
	int result = 0;
	for(int i = 0; i < xcyr ; i++ ){
		result += X[xr][i] * Y[i][yc];
	}
	cout << "Doing X row: " << xr << " and Y column: " << yc << " = ";
	cout << result << '\n';
	Z[xr][yc] = result;
}


void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc ){
	
	for(int i = 0; i < xr ; i++){
		for(int j = 0; j < yc ; j++){
			multiply(Z,X,i,xc,Y,j);
		}
	}
	
}
