#pragma once
#include "Point3D.h"
#include "Camera.h"
#include "DrawableObject.h"
#include "Matrix41.h"
#include "Matrix44.h"

class TransformHandler
{
private:
	
public:
	TransformHandler(void);
	Matrix41 *multiplyMatrices(Matrix44 *mat44, Matrix41 *mat41);
	void rotateX(Point3D *_p, float _degrees);
	void rotateObjectX(DrawableObject *_obj, float _degrees);
	void rotateY(Point3D *_p, float _degrees);
	void rotateObjectY(DrawableObject *_obj, float _degrees);
	void rotateZ(Point3D *_p, float _degrees);
	void rotateObjectZ(DrawableObject *_obj, float _degrees);
	void translate(Point3D *_p, float _offsetX, float _offsetY, float _offsetZ);
	void translateObject(DrawableObject *_obj, float _offsetX, float _offsetY, float _offsetZ);
	void translateObjectPosition(DrawableObject *_obj, float _offsetX, float _offsetY, float _offsetZ);
	void scaleUniform(Point3D *_p, float _factor);
	void scaleObjectUniform(DrawableObject *_obj, float _factor);
	void toNDC(Point3D *_p, float _near, float _far, float _height, float _width);
	void objectToNDC(DrawableObject *_obj, Camera *camera);
	void toViewSpace(Point3D *_p, Point3D *_u, Point3D *_v, Point3D *_n);
	void objectToViewSpace(DrawableObject *_obj, Camera *camera);
	~TransformHandler(void);
};

