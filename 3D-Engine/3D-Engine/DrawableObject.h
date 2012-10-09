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
	vector<Triangle*> *triangles;
public:
	DrawableObject(void);
	DrawableObject(vector<Triangle*> *_triangles);
	void addTriangle(Triangle *_triangle);
	vector<Triangle*> *getTriangles();
	~DrawableObject(void);
};

