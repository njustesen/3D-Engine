#include "Point3D.h"

#pragma once
class TransformHandler
{
private:
	
public:
	TransformHandler(void);
	Point3D *multiplyMatrices(float a[4][4], float matrixB[4][1]);
	Point3D *rotateX(Point3D *_p, float _degrees);
	Point3D *rotateY(Point3D *_p, float _degrees);
	Point3D *rotateZ(Point3D *_p, float _degrees);
	Point3D *translate(Point3D *_p, float _offsetX, float _offsetY, float _offsetZ);
	Point3D *scaleUniform(Point3D *_p, float _factor);
	Point3D *projectToNDC(Point3D *_p, float _near, float _far, float _height, float _width);
	Point3D *toViewSpace(Point3D *_p, Point3D *_u, Point3D *_v, Point3D *_n);
	~TransformHandler(void);
};

