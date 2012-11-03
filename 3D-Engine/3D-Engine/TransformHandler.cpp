#include "TransformHandler.h"
#include "Camera.h"
#include <math.h>
#include "main.h"

#define PI 3.14159265

TransformHandler::TransformHandler(void)
{
}

Matrix41 *TransformHandler::multiplyMatrices(Matrix44 *mat44, Matrix41 *mat41){

	float result[4][1] = {{ 0.0f },{ 0.0f },{ 0.0f },{ 0.0f }};

	for (int a = 0; a < 4; a++){ 

		for (int b = 0; b < 4; b++){

			result[b][0] += mat41->getValue(a) * mat44->getValue(b,a);

		}

	}

	return new Matrix41(result);
}

void TransformHandler::rotateX(Point3D *_p, float _degrees){

	float cosD = cosf(_degrees);
	float sinD = sinf(_degrees);

	float mat44[4][4] =
		{
		{ 1.0f,	0.0f, 0.0f, 0.0f },
		{ 0.0f,	cosD, -sinD, 0.0f },
		{ 0.0f,	sinD, cosD, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float mat41[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	Matrix41 * m41 = new Matrix41(mat41);
	Matrix44 * m44 = new Matrix44(mat44);
	Matrix41 * result = multiplyMatrices(m44, m41);

	_p->setX(result->getValue(0));
	_p->setY(result->getValue(1));
	_p->setZ(result->getValue(2));

	delete result;
	delete m41;
	delete m44;
}

void TransformHandler::rotateObjectX(DrawableObject *_obj, float _degrees){

	for(unsigned int t = 0; t < _obj->getTriangles()->size(); t++){
		rotateX(_obj->getTriangles()->at(t)->getA(), _degrees);
		rotateX(_obj->getTriangles()->at(t)->getB(), _degrees);
		rotateX(_obj->getTriangles()->at(t)->getC(), _degrees);
	}

}

void TransformHandler::rotateY(Point3D *_p, float _degrees){

	float cosD = cosf(_degrees);
	float sinD = sinf(_degrees);

	float mat44[4][4] =
		{
		{ cosD,	0.0f, sinD, 0.0f },
		{ 0.0f,	1.0f, 0.0f, 0.0f },
		{ -sinD,0.0f, cosD, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float mat41[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	Matrix41 * m41 = new Matrix41(mat41);
	Matrix44 * m44 = new Matrix44(mat44);
	Matrix41 * result = multiplyMatrices(m44, m41);

	_p->setX(result->getValue(0));
	_p->setY(result->getValue(1));
	_p->setZ(result->getValue(2));

	delete result;
	delete m41;
	delete m44;
}

void TransformHandler::rotateObjectY(DrawableObject *_obj, float _degrees){

	for(unsigned int t = 0; t < _obj->getTriangles()->size(); t++){
		rotateY(_obj->getTriangles()->at(t)->getA(), _degrees);
		rotateY(_obj->getTriangles()->at(t)->getB(), _degrees);
		rotateY(_obj->getTriangles()->at(t)->getC(), _degrees);
	}

}

void TransformHandler::rotateZ(Point3D *_p, float _degrees){

	float cosD = cosf(_degrees);
	float sinD = sinf(_degrees);

	float mat44[4][4] =
		{
		{ cosD,	-sinD, 0.0f, 0.0f },
		{ sinD,	cosD, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float mat41[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	Matrix41 * m41 = new Matrix41(mat41);
	Matrix44 * m44 = new Matrix44(mat44);
	Matrix41 * result = multiplyMatrices(m44, m41);

	_p->setX(result->getValue(0));
	_p->setY(result->getValue(1));
	_p->setZ(result->getValue(2));

	delete result;
	delete m41;
	delete m44;
}

void TransformHandler::rotateObjectZ(DrawableObject *_obj, float _degrees){

	for(unsigned int t = 0; t < _obj->getTriangles()->size(); t++){
		rotateZ(_obj->getTriangles()->at(t)->getA(), _degrees);
		rotateZ(_obj->getTriangles()->at(t)->getB(), _degrees);
		rotateZ(_obj->getTriangles()->at(t)->getC(), _degrees);
	}

}

void TransformHandler::translate(Point3D *_p, float _offsetX, float _offsetY, float _offsetZ){

	float mat44[4][4] =
		{
		{ 1.0f,	0.0f, 0.0f, _offsetX },
		{ 0.0f,	1.0f, 0.0f, _offsetY },
		{ 0.0f, 0.0f, 1.0f, _offsetZ },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float mat41[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};
	
	Matrix41 * m41 = new Matrix41(mat41);
	Matrix44 * m44 = new Matrix44(mat44);
	Matrix41 * result = multiplyMatrices(m44, m41);

	_p->setX(result->getValue(0));
	_p->setY(result->getValue(1));
	_p->setZ(result->getValue(2));

	delete result;
	delete m41;
	delete m44;
	
}

void TransformHandler::translateObject(DrawableObject *_obj, float _offsetX, float _offsetY, float _offsetZ){

	for(unsigned int t = 0; t < _obj->getTriangles()->size(); t++){
		translate(_obj->getTriangles()->at(t)->getA(), _offsetX, _offsetY, _offsetZ);
		translate(_obj->getTriangles()->at(t)->getB(), _offsetX, _offsetY, _offsetZ);
		translate(_obj->getTriangles()->at(t)->getC(), _offsetX, _offsetY, _offsetZ);
	}

}

void TransformHandler::translateObjectPosition(DrawableObject *_obj, float _offsetX, float _offsetY, float _offsetZ){

	translate(_obj->getPosition(), _offsetX, _offsetY, _offsetZ);

}

void TransformHandler::scaleUniform(Point3D *_p, float _factor){

	float mat44[4][4] =
		{
		{ _factor, 0.0f, 0.0f, 0.0f },
		{ 0.0f,	_factor, 0.0f, 0.0f },
		{ 0.0f, 0.0f, _factor, 0.0f },
		{ 0.0f,	0.0f, 0.0f, 1.0f },
		};

	float mat41[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	Matrix41 * m41 = new Matrix41(mat41);
	Matrix44 * m44 = new Matrix44(mat44);
	Matrix41 * result = multiplyMatrices(m44, m41);

	_p->setX(result->getValue(0));
	_p->setY(result->getValue(1));
	_p->setZ(result->getValue(2));

	delete result;
	delete m41;
	delete m44;
}

void TransformHandler::scaleObjectUniform(DrawableObject *_obj, float _factor){

	for(unsigned int t = 0; t < _obj->getTriangles()->size(); t++){
		scaleUniform(_obj->getTriangles()->at(t)->getA(), _factor);
		scaleUniform(_obj->getTriangles()->at(t)->getB(), _factor);
		scaleUniform(_obj->getTriangles()->at(t)->getC(), _factor);
	}

}

void TransformHandler::toNDC(Point3D *_p, float _near, float _far, float _height, float _width){

	float mat44[4][4] =
		{
		{ (2 * _near) / _width, 0.0f, 0.0f, 0.0f },
		{ 0.0f,	(2 * _near) / _height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, (-(_far + _near)) / (_far - _near), (-2*(_far * _near)) / (_far - _near) },
		{ 0.0f,	0.0f, -1.0f, 0.0f },
		};

	float mat41[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	Matrix41 * m41 = new Matrix41(mat41);
	Matrix44 * m44 = new Matrix44(mat44);
	Matrix41 * result = multiplyMatrices(m44, m41);

	// Make sure to normalize with w
	_p->setX(result->getValue(0) / result->getValue(3));
	_p->setY(result->getValue(1) / result->getValue(3));
	_p->setZ(result->getValue(2) / result->getValue(3));

	delete result;
	delete m41;
	delete m44;
}

void TransformHandler::objectToNDC(DrawableObject *_obj, Camera *camera){

	float near = camera->getNear();
	float far = camera->getFar();
	float angle = camera->getHorizontalViewAngle() * PI/180;
	float width = (tan(angle / 2) * near) * 2;
	float height = width / (SCREEN_WIDTH / SCREEN_HEIGHT);

	for(unsigned int t = 0; t < _obj->getTriangles()->size(); t++){
		toNDC(_obj->getTriangles()->at(t)->getA(), near, far, height, width);
		toNDC(_obj->getTriangles()->at(t)->getB(), near, far, height, width);
		toNDC(_obj->getTriangles()->at(t)->getC(), near, far, height, width);
	}

}

void TransformHandler::toViewSpace(Point3D *_p, Point3D *_u, Point3D *_v, Point3D *_n){

	float mat44[4][4] =
		{
		{ _u->getX(), _u->getY(), _u->getZ(), 0.0f },
		{ _v->getX(), _v->getY(), _v->getZ(), 0.0f },
		{ _n->getX(), _n->getY(), _n->getZ(), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};

	float mat41[4][1] =
		{
		{ _p->getX() },
		{ _p->getY() },
		{ _p->getZ() },
		{ 1.0f },
		};

	Matrix41 * m41 = new Matrix41(mat41);
	Matrix44 * m44 = new Matrix44(mat44);
	Matrix41 * result = multiplyMatrices(m44, m41);

	_p->setX(result->getValue(0));
	_p->setY(result->getValue(1));
	_p->setZ(result->getValue(2));

	delete result;
	delete m41;
	delete m44;
}

void TransformHandler::objectToViewSpace(DrawableObject *_obj, Camera *camera){

	Point3D * u = camera->getIntermediateOrthogonalAxis();	// New X
	Point3D * v = camera->getNewYAxis();					// New Y
	Point3D * n = camera->getViewPlaneNormal();				// New Z

	for(unsigned int t = 0; t < _obj->getTriangles()->size(); t++){
		toViewSpace(_obj->getTriangles()->at(t)->getA(), u, v, n);
		toViewSpace(_obj->getTriangles()->at(t)->getB(), u, v, n);
		toViewSpace(_obj->getTriangles()->at(t)->getC(), u, v, n);
	}

	delete u;
	delete v;
	delete n;

}

TransformHandler::~TransformHandler(void)
{
}
