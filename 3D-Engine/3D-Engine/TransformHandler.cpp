#include "TransformHandler.h"
#include <math.h>

TransformHandler::TransformHandler(void)
{
}

Point3D *TransformHandler::multiplyMatrices(float a[4][4], float b[4][1]){
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

	return new Point3D(c[0][0], c[1][0], c[2][0]);
}

Point3D *TransformHandler::rotateX(Point3D *_p, float _degrees){

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

Point3D *TransformHandler::rotateY(Point3D *_p, float _degrees){

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

Point3D *TransformHandler::rotateZ(Point3D *_p, float _degrees){

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

Point3D *TransformHandler::translate(Point3D *_p, float _offsetX, float _offsetY, float _offsetZ){

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

Point3D *TransformHandler::scaleUniform(Point3D *_p, float _factor){

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

Point3D *TransformHandler::projectToNDC(Point3D *_p, float _near, float _far, float _height, float _width){
	float matrixA[4][4] =
		{
		{ (2 * _near) / _width, 0.0f, 0.0f, 0.0f },
		{ 0.0f,	(2 * _near) / _height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, (-(_far + _near)) / (_far - _near), (-2*(_far * _near)) / (_far - _near) },
		{ 0.0f,	0.0f, -1.0f, 0.0f },
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

Point3D *TransformHandler::toViewSpace(Point3D *_p, Point3D *_u, Point3D *_v, Point3D *_n){

	float matrixA[4][4] =
		{
		{ _u->getX(), _u->getY(), _u->getZ(), 0.0f },
		{ _v->getX(), _v->getY(), _v->getZ(), 0.0f },
		{ _n->getX(), _n->getY(), _n->getZ(), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
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
