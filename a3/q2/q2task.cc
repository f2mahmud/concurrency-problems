#if defined(TASK)
#include "q2task.h"

MatrixMultiplier::MatrixMultiplier(unsigned int rowNumber, unsigned int parentRow):rowNumber(rowNumber), parentRow(parentRow){}

void MatrixMultiplier::main(){
	
	unsigned int distanceToMiddle = floor(rowNumber / 2);
		
	if(distanceToMiddle == 0){
		distanceToMiddle =1 ;
	}
		
	unsigned int higherRow = rowNumber + distanceToMiddle;
	unsigned int lowerRow = rowNumber - distanceToMiddle;
		
	if(lowerRow >= 0 && lowerRow <= parentRow && rowNumber != MatrixMultiplier::xr - 1){
		MatrixMultiplier lower(lowerRow, rowNumber);
	}
		
	if(higherRow > parentRow && higherRow < MatrixMultiplier::xr&& rowNumber != 0){
		MatrixMultiplier higher(higherRow, rowNumber);
	}
		
	int result;
		
	for(unsigned int i = 0 ; i < MatrixMultiplier::yc; i ++){
		result = 0;
		for(unsigned int j = 0 ; j < MatrixMultiplier::xcyr ; j++){
			result += X[rowNumber][j] * Y[j][i];
		}
		Z[rowNumber][i] = result;
	}
		
}

#endif