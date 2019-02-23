#include<iostream>
#include <cmath>  
#include <algorithm> 

_Task MatrixMultiplier{
	
public:

	static unsigned int xr, xcyr, yc;
	static int **Z, **X, **Y;
	
	MatrixMultiplier(unsigned int rowNumber, unsigned int parentRow);
	
private: 

	unsigned int rowNumber, parentRow;
	
	void main();
	
};