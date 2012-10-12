#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "TransformHandler.h"
#include <vector>
#include "Triangle.h"
using namespace std;

#pragma once
class DrawableObject
{
private:
	Point3D *position;
	vector<Triangle*> *triangles;
public:
	DrawableObject *clone();
	DrawableObject(Point3D *_position);
	DrawableObject(Point3D *_position, vector<Triangle*> *_triangles);
	void rotateX(TransformHandler *_handler, float _degrees);
	void rotateY(TransformHandler *_handler, float _degrees);
	void rotateZ(TransformHandler *_handler, float _degrees);
	void translate(TransformHandler *_handler, float _offsetX, float _offsetY, float _offsetZ);
	void scaleUniform(TransformHandler *_handler, float _factor);
	void addTriangle(Triangle *_triangle);
	vector<Triangle*> *getTriangles();
	Point3D *getPosition();
	void setPosition(Point3D *_position);
	void projectToNDC(TransformHandler *_handler, float _near, float _far, float _height, float _width);
	void transformToViewSpace(TransformHandler *_handler, Point3D *_u, Point3D *_v, Point3D *_n);
	~DrawableObject(void);
};

