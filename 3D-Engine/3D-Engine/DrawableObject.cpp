#include "DrawableObject.h"


DrawableObject::DrawableObject(vector<Triangle*> *_triangles)
{
	triangles = _triangles;
}

DrawableObject::DrawableObject(void)
{
	triangles = new vector<Triangle*>();
}

void DrawableObject::addTriangle(Triangle *_triangle){
	triangles->push_back(_triangle);
}

vector<Triangle*> *DrawableObject::getTriangles(){
	return triangles;
}

DrawableObject::~DrawableObject(void)
{
}
