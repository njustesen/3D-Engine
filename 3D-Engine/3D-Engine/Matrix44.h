#pragma once
class Matrix44
{

private: 
	float matrixArray[4][4];

public:
	Matrix44(float mat[4][4]);
	float getValue(int row, int col);
	void setValue(int row, int col, float val);
	~Matrix44(void);
};

