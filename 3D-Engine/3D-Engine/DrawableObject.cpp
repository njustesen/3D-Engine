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

void DrawableObject::rotateX(TransformHandler *_handler, float _degrees){
	for (int i = 0; i < triangles->size(); i++){
		Point3D *ppa = triangles->at(i)->getA();
		Point3D *paa = _handler->rotateX(ppa, _degrees);
		triangles->at(i)->setA(paa);
			
		Point3D *ppb = triangles->at(i)->getB();
		Point3D *pab = _handler->rotateX(ppb, _degrees);
		triangles->at(i)->setB(pab);

		Point3D *ppc = triangles->at(i)->getC();
		Point3D *pac = _handler->rotateX(ppc, _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::rotateY(TransformHandler *_handler, float _degrees){
	for (int i = 0; i < triangles->size(); i++){
		Point3D *ppa = triangles->at(i)->getA();
		Point3D *paa = _handler->rotateY(ppa, _degrees);
		triangles->at(i)->setA(paa);
			
		Point3D *ppb = triangles->at(i)->getB();
		Point3D *pab = _handler->rotateY(ppb, _degrees);
		triangles->at(i)->setB(pab);

		Point3D *ppc = triangles->at(i)->getC();
		Point3D *pac = _handler->rotateY(ppc, _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::rotateZ(TransformHandler *_handler, float _degrees){
	for (int i = 0; i < triangles->size(); i++){
		Point3D *ppa = triangles->at(i)->getA();
		Point3D *paa = _handler->rotateZ(ppa, _degrees);
		triangles->at(i)->setA(paa);
			
		Point3D *ppb = triangles->at(i)->getB();
		Point3D *pab = _handler->rotateZ(ppb, _degrees);
		triangles->at(i)->setB(pab);

		Point3D *ppc = triangles->at(i)->getC();
		Point3D *pac = _handler->rotateZ(ppc, _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::translate(TransformHandler *_handler, float _offsetX, float _offsetY, float _offsetZ){
	position = _handler->translate(position, _offsetX, _offsetY, _offsetZ);
	
}

void DrawableObject::scaleUniform(TransformHandler *_handler, float _factor){
	for (int i = 0; i < triangles->size(); i++){
		Point3D *ppa = triangles->at(i)->getA();
		Point3D *paa = _handler->scaleUniform(ppa, _factor);
		triangles->at(i)->setA(paa);
			
		Point3D *ppb = triangles->at(i)->getB();
		Point3D *pab = _handler->scaleUniform(ppb, _factor);
		triangles->at(i)->setB(pab);

		Point3D *ppc = triangles->at(i)->getC();
		Point3D *pac = _handler->scaleUniform(ppc, _factor);
		triangles->at(i)->setC(pac);
	}
}

Point3D *DrawableObject::getPosition(){
	return position;
}

void DrawableObject::setPosition(Point3D *_position){
	//delete position;
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
}
