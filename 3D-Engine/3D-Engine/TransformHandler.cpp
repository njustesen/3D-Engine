#include "TransformHandler.h"
#include <math.h>

TransformHandler::TransformHandler(void)
{
}

Point *TransformHandler::multiplyMatrices(float a[4][4], float b[4][1]){
	// Resulting matrix
	float c[4][1] = 
		{
		{ 0.0f },
		{ 0.0f },
		{ 0.0f },
		{ 0.0f },
		};

	// Iterate over matrix b
	for (int ax = 0; ax < 4; ax++){ 

		// Iterate over matrix a
		for (int bx = 0; bx < 4; bx++){

			// Multiply into c
			c[bx][0] += b[ax][0] * a[bx][ax];

		}

	}

	return new Point(c[0][0], c[1][0], c[2][0]);
}

Point *TransformHandler::rotateX(Point *_p, float _degrees){

	float cosD = cosf(_degrees);
	float sinD = sinf(_degrees);

	float matrixA[4][4] =
		{
		{ 1.0f,	0.0f, 0.0f, 0.0f },
		{ 0.0f,	cosD, -sinD, 0.0f },
		{ 0.0f,	sinD, cosD, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float matrixB[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	return multiplyMatrices(matrixA, matrixB);
}

Point *TransformHandler::rotateY(Point *_p, float _degrees){

	float cosD = cosf(_degrees);
	float sinD = sinf(_degrees);

	float matrixA[4][4] =
		{
		{ cosD,	0.0f, sinD, 0.0f },
		{ 0.0f,	1.0f, 0.0f, 0.0f },
		{ -sinD,0.0f, cosD, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float matrixB[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	return multiplyMatrices(matrixA, matrixB);
}

Point *TransformHandler::rotateZ(Point *_p, float _degrees){

	float cosD = cosf(_degrees);
	float sinD = sinf(_degrees);

	float matrixA[4][4] =
		{
		{ cosD,	-sinD, 0.0f, 0.0f },
		{ sinD,	cosD, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float matrixB[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	return multiplyMatrices(matrixA, matrixB);
}

Point *TransformHandler::translate(Point *_p, float _offsetX, float _offsetY, float _offsetZ){

	float matrixA[4][4] =
		{
		{ 1.0f,	0.0f, 0.0f, _offsetX },
		{ 0.0f,	1.0f, 0.0f, _offsetY },
		{ 0.0f, 0.0f, 1.0f, _offsetZ },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float matrixB[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	return multiplyMatrices(matrixA, matrixB);
}

Point *TransformHandler::scaleUniform(Point *_p, float _factor){

	float matrixA[4][4] =
		{
		{ _factor, 0.0f, 0.0f, 0.0f },
		{ 0.0f,	_factor, 0.0f, 0.0f },
		{ 0.0f, 0.0f, _factor, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float matrixB[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	return multiplyMatrices(matrixA, matrixB);
}

TransformHandler::~TransformHandler(void)
{
}
