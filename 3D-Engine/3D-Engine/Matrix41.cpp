#include "Matrix41.h"


Matrix41::Matrix41(float mat[4][1])
{
	for(int r = 0; r < 4; r++){
		matrixArray[r][0] = mat[r][0];
	}
}

float Matrix41::getValue(int row){
	return matrixArray[row][0];
}

void Matrix41::setValue(int row, float val){
	matrixArray[row][0] = val;
}


Matrix41::~Matrix41(void){

}
