#include "Point3D.h"
#include "Matrix41.h"
#include "Matrix44.h"

#pragma once
class TransformHandler
{
private:
	
public:
	TransformHandler(void);
	Matrix41 *multiplyMatrices(Matrix44 *mat44, Matrix41 *mat41);
	void rotateX(Point3D *_p, float _degrees);
	void rotateX(DrawableObject *_obj, float _degrees);
	void rotateY(Point3D *_p, float _degrees);
	void rotateY(DrawableObject *_obj, float _degrees);
	void rotateZ(Point3D *_p, float _degrees);
	void rotateZ(DrawableObject *_obj, float _degrees);
	void translate(Point3D *_p, float _offsetX, float _offsetY, float _offsetZ);
	void translate(DrawableObject *_obj, float _offsetX, float _offsetY, float _offsetZ);
	void scaleUniform(Point3D *_p, float _factor);
	void scaleUniform(DrawableObject *_obj, float _factor);
	void projectToNDC(Point3D *_p, float _near, float _far, float _height, float _width);
	void projectToNDC(DrawableObject *_obj, float _near, float _far, float _height, float _width);
	void toViewSpace(Point3D *_p, Point3D *_u, Point3D *_v, Point3D *_n);
	void toViewSpace(DrawableObject *_obj, Point3D *_u, Point3D *_v, Point3D *_n);
	~TransformHandler(void);
};

