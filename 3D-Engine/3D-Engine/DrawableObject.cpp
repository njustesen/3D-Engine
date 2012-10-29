#include "DrawableObject.h"

DrawableObject::DrawableObject(Point3D *_position, vector<Triangle*> *_triangles)
{
	triangles = _triangles;
	position = _position;
}

DrawableObject::DrawableObject(Point3D *_position)
{
	triangles = new vector<Triangle*>();
	position = _position;
}

void DrawableObject::addTriangle(Triangle *_triangle){
	triangles->push_back(_triangle);
}

vector<Triangle*> *DrawableObject::getTriangles(){
	return triangles;
}

Point3D *DrawableObject::getPosition(){
	return position;
}

void DrawableObject::setPosition(Point3D *_position){
	if (position)
		delete position;

	position = _position;
}

DrawableObject *DrawableObject::clone(){

	vector<Triangle*> *triClone = new vector<Triangle*>();

	for(int i = 0; i < triangles->size(); i++){
		Point3D *clonedPoint3DA = new Point3D(triangles->at(i)->getA()->getX(), triangles->at(i)->getA()->getY(), triangles->at(i)->getA()->getZ());
		Point3D *clonedPoint3DB = new Point3D(triangles->at(i)->getB()->getX(), triangles->at(i)->getB()->getY(), triangles->at(i)->getB()->getZ());
		Point3D *clonedPoint3DC = new Point3D(triangles->at(i)->getC()->getX(), triangles->at(i)->getC()->getY(), triangles->at(i)->getC()->getZ());
		Triangle *clonedTriangle = new Triangle(clonedPoint3DA, clonedPoint3DB, clonedPoint3DC);
		triClone->push_back(clonedTriangle);
	}

	Point3D *clonedPosition = new Point3D(position->getX(), position->getY(), position->getZ());

	return new DrawableObject(clonedPosition, triClone);
}

DrawableObject::~DrawableObject(void)
{
	if (position)
		delete position;

	for(int i = 0; i < triangles->size(); i++){
		if (triangles->at(i))
			delete triangles->at(i);
	}

	if (triangles)
		delete triangles;
}
