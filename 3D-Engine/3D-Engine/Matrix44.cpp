#include "Matrix44.h"


Matrix44::Matrix44(float mat[4][4])
{
	for(int r = 0; r < 4; r++){
		for(int c = 0; c < 4; c++){
			matrixArray[r][c] = mat[r][c];
		}
	}
}

float Matrix44::getValue(int row, int col){
	return matrixArray[row][col];
}

void Matrix44::setValue(int row, int col, float val){
	matrixArray[row][col] = val;
}

Matrix44::~Matrix44(void){

}
