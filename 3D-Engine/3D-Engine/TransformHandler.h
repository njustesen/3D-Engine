#include "Point.h"

#pragma once
class TransformHandler
{
private:
	
public:
	TransformHandler(void);
	Point *multiplyMatrices(float a[4][4], float matrixB[4][1]);
	Point *rotateX(Point *_p, float _degrees);
	Point *rotateY(Point *_p, float _degrees);
	Point *rotateZ(Point *_p, float _degrees);
	Point *translate(Point *_p, float _offsetX, float _offsetY, float _offsetZ);
	Point *scaleUniform(Point *_p, float _factor);
	~TransformHandler(void);
};

