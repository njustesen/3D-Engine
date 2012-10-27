#pragma once
class Matrix41
{

private: 
	float matrixArray[4][1];

public:
	Matrix41(float mat[4][1]);
	float getValue(int row);
	void setValue(int row, float val);
	~Matrix41(void);
};

