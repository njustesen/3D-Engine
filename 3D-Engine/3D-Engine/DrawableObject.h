#pragma once
#include "SDL.h"
#include <string>
#include "SDL_image.h"
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
	void addTriangle(Triangle *_triangle);
	vector<Triangle*> *getTriangles();
	Point3D *getPosition();
	void setPosition(Point3D *_position);
	~DrawableObject(void);
};

