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
		Point3D *paa = _handler->rotateX(triangles->at(i)->getA(), _degrees);
		triangles->at(i)->setA(paa);
			
		Point3D *pab = _handler->rotateX(triangles->at(i)->getB(), _degrees);
		triangles->at(i)->setB(pab);

		Point3D *pac = _handler->rotateX(triangles->at(i)->getC(), _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::rotateY(TransformHandler *_handler, float _degrees){
	for (int i = 0; i < triangles->size(); i++){
		Point3D *paa = _handler->rotateY(triangles->at(i)->getA(), _degrees);
		triangles->at(i)->setA(paa);
			
		Point3D *pab = _handler->rotateY(triangles->at(i)->getB(), _degrees);
		triangles->at(i)->setB(pab);

		Point3D *pac = _handler->rotateY(triangles->at(i)->getC(), _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::rotateZ(TransformHandler *_handler, float _degrees){
	for (int i = 0; i < triangles->size(); i++){
		Point3D *paa = _handler->rotateZ(triangles->at(i)->getA(), _degrees);
		triangles->at(i)->setA(paa);

		Point3D *pab = _handler->rotateZ(triangles->at(i)->getB(), _degrees);
		triangles->at(i)->setB(pab);

		Point3D *pac = _handler->rotateZ(triangles->at(i)->getC(), _degrees);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::translate(TransformHandler *_handler, float _offsetX, float _offsetY, float _offsetZ){
	setPosition(_handler->translate(position, _offsetX, _offsetY, _offsetZ));
	
}

void DrawableObject::scaleUniform(TransformHandler *_handler, float _factor){
	for (int i = 0; i < triangles->size(); i++){
		Point3D *paa = _handler->scaleUniform(triangles->at(i)->getA(), _factor);
		triangles->at(i)->setA(paa);
			
		Point3D *pab = _handler->scaleUniform(triangles->at(i)->getB(), _factor);
		triangles->at(i)->setB(pab);

		Point3D *pac = _handler->scaleUniform(triangles->at(i)->getC(), _factor);
		triangles->at(i)->setC(pac);
	}
}

void DrawableObject::projectToNDC(TransformHandler *_handler, float _near, float _far, float _height, float _width){
	for (int i = 0; i < triangles->size(); i++){
		triangles->at(i)->setA( _handler->projectToNDC(triangles->at(i)->getA(), _near, _far, _height, _width ));
		triangles->at(i)->setB( _handler->projectToNDC(triangles->at(i)->getB(), _near, _far, _height, _width ));
		triangles->at(i)->setC( _handler->projectToNDC(triangles->at(i)->getC(), _near, _far, _height, _width ));
	}
	setPosition(_handler->projectToNDC(position, _near, _far, _height, _width ));
}

void DrawableObject::transformToViewSpace(TransformHandler *_handler, Point3D *_u, Point3D *_v, Point3D *_n) {

	float matrixA[4][4] =
		{
		{ _u->getX(), _u->getY(), _u->getZ(), 0.0f },
		{ _v->getX(), _v->getY(), _v->getZ(), 0.0f },
		{ _n->getX(), _n->getY(), _n->getZ(), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};

	for (int i = 0; i < triangles->size(); i++){
		triangles->at(i)->setA(_handler->toViewSpace(triangles->at(i)->getA(), _u, _v, _n));
		triangles->at(i)->setB(_handler->toViewSpace(triangles->at(i)->getB(), _u, _v, _n));
		triangles->at(i)->setC(_handler->toViewSpace(triangles->at(i)->getC(), _u, _v, _n));
	}

	setPosition(_handler->toViewSpace(position, _u, _v, _n));

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
