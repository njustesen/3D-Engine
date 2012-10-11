#include "DrawableObject.h"


DrawableObject::DrawableObject(Point *_position, vector<Triangle*> *_triangles)
{
	triangles = _triangles;
	position = _position;
}

DrawableObject::DrawableObject(Point *_position)
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
		Point *ppa = triangles->at(i)->getA();
		Point *paa = _handler->rotateX(ppa, _degrees);
		triangles->at(i)->setA(paa);
			
		Point *ppb = triangles->at(i)->getB();
		Point *pab = _handler->rotateX(ppb, _degrees);
		triangles->at(i)->setB(pab);

		Point *ppc = triangles->at(i)->getC();
		Point *pac = _handler->rotateX(ppc, _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::rotateY(TransformHandler *_handler, float _degrees){
	for (int i = 0; i < triangles->size(); i++){
		Point *ppa = triangles->at(i)->getA();
		Point *paa = _handler->rotateY(ppa, _degrees);
		triangles->at(i)->setA(paa);
			
		Point *ppb = triangles->at(i)->getB();
		Point *pab = _handler->rotateY(ppb, _degrees);
		triangles->at(i)->setB(pab);

		Point *ppc = triangles->at(i)->getC();
		Point *pac = _handler->rotateY(ppc, _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::rotateZ(TransformHandler *_handler, float _degrees){
	for (int i = 0; i < triangles->size(); i++){
		Point *ppa = triangles->at(i)->getA();
		Point *paa = _handler->rotateZ(ppa, _degrees);
		triangles->at(i)->setA(paa);
			
		Point *ppb = triangles->at(i)->getB();
		Point *pab = _handler->rotateZ(ppb, _degrees);
		triangles->at(i)->setB(pab);

		Point *ppc = triangles->at(i)->getC();
		Point *pac = _handler->rotateZ(ppc, _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::translate(TransformHandler *_handler, float _offsetX, float _offsetY, float _offsetZ){
	for (int i = 0; i < triangles->size(); i++){
		Point *ppa = triangles->at(i)->getA();
		Point *paa = _handler->translate(ppa, _offsetX, _offsetY, _offsetZ);
		triangles->at(i)->setA(paa);
			
		Point *ppb = triangles->at(i)->getB();
		Point *pab = _handler->translate(ppa, _offsetX, _offsetY, _offsetZ);
		triangles->at(i)->setB(pab);

		Point *ppc = triangles->at(i)->getC();
		Point *pac = _handler->translate(ppa, _offsetX, _offsetY, _offsetZ);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::scaleUniform(TransformHandler *_handler, float _factor){
	for (int i = 0; i < triangles->size(); i++){
		Point *ppa = triangles->at(i)->getA();
		Point *paa = _handler->scaleUniform(ppa, _factor);
		triangles->at(i)->setA(paa);
			
		Point *ppb = triangles->at(i)->getB();
		Point *pab = _handler->scaleUniform(ppb, _factor);
		triangles->at(i)->setB(pab);

		Point *ppc = triangles->at(i)->getC();
		Point *pac = _handler->scaleUniform(ppc, _factor);
		triangles->at(i)->setC(pac);
	}
}

Point *DrawableObject::getPosition(){
	return position;
}

void DrawableObject::setPosition(Point *_position){
	//delete position;
	position = _position;
}

DrawableObject *DrawableObject::clone(){

	vector<Triangle*> *triClone = new vector<Triangle*>();

	for(int i = 0; i < triangles->size(); i++){
		Point *clonedPointA = new Point(triangles->at(i)->getA()->getX(), triangles->at(i)->getA()->getY(), triangles->at(i)->getA()->getZ());
		Point *clonedPointB = new Point(triangles->at(i)->getB()->getX(), triangles->at(i)->getB()->getY(), triangles->at(i)->getB()->getZ());
		Point *clonedPointC = new Point(triangles->at(i)->getC()->getX(), triangles->at(i)->getC()->getY(), triangles->at(i)->getC()->getZ());
		Triangle *clonedTriangle = new Triangle(clonedPointA, clonedPointB, clonedPointC);
		triClone->push_back(clonedTriangle);
	}

	Point *clonedPosition = new Point(position->getX(), position->getY(), position->getZ());

	return new DrawableObject(clonedPosition, triClone);
}

DrawableObject::~DrawableObject(void)
{
}
