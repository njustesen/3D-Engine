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
	Point *position;
	vector<Triangle*> *triangles;
public:
	DrawableObject *clone();
	DrawableObject(Point *_position);
	DrawableObject(Point *_position, vector<Triangle*> *_triangles);
	void rotateX(TransformHandler *_handler, float _degrees);
	void rotateY(TransformHandler *_handler, float _degrees);
	void rotateZ(TransformHandler *_handler, float _degrees);
	void translate(TransformHandler *_handler, float _offsetX, float _offsetY, float _offsetZ);
	void scaleUniform(TransformHandler *_handler, float _factor);
	void addTriangle(Triangle *_triangle);
	vector<Triangle*> *getTriangles();
	Point *getPosition();
	void setPosition(Point *_position);
	~DrawableObject(void);
};

