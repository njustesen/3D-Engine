#include "Camera.h"
#include "Point.h"
#include "SDL.h"
#include "main.h"
#include <vector>
#include "DrawableObject.h"

Camera::Camera(Point *_position, Point *_lookingAt, TransformHandler *_handler){
	position = _position;
	lookingAt = _lookingAt;
	handler = _handler;
}

Point *Camera::getPosition(){
	return position;
}

Point *Camera::getLookingAt(){
	return lookingAt;
}

void Camera::setLookingAt(Point *_point){
	lookingAt = _point;
}

void Camera::setPosition(Point *_point){
	position = _point;
}

Point *Camera::getUpVector(){

	Point v(0.0f, 1.0f, 0.0f);

	Point right(lookingAt->getY() * v.getZ() - lookingAt->getZ() * v.getY(),
				lookingAt->getZ() * v.getX() - lookingAt->getX() * v.getZ(),
				lookingAt->getX() * v.getY() - lookingAt->getY() * v.getX());

	return new Point(	right.getY() * lookingAt->getZ() - right.getZ() * lookingAt->getY(),
						right.getZ() * lookingAt->getX() - right.getX() * lookingAt->getZ(),
						right.getX() * lookingAt->getY() - right.getY() * lookingAt->getX());

}

Point *Camera::getIntermediateOrthogonalAxis(Point *_up, Point *_n){
	Point cross(_up->getY() * _n->getZ() - _up->getZ() * _n->getY(),
				_up->getZ() * _n->getX() - _up->getX() * _n->getZ(),
				_up->getX() * _n->getY() - _up->getY() * _n->getX());

	float length = sqrt((cross.getX() * cross.getX()) +
						(cross.getY() * cross.getY()) +
						(cross.getZ() * cross.getZ()));

	return new Point(cross.getX() / length, cross.getY() / length, cross.getZ() / length);

}

Point *Camera::getNewYAxis(Point *_n, Point *_u){
	return new Point(	_n->getY() * _u->getZ() - _n->getZ() * _u->getY(),
						_n->getZ() * _u->getX() - _n->getX() * _u->getZ(),
						_n->getX() * _u->getY() - _n->getY() * _u->getX());
}

void Camera::transformToViewSpace(DrawableObject *_object, Point *_u, Point *_v, Point *_n){
	float matrixA[4][4] =
		{
		{ _u->getX(), _u->getY(), _u->getZ(), 0.0f },
		{ _v->getX(), _v->getY(), _v->getZ(), 0.0f },
		{ _n->getX(), _n->getY(), _n->getZ(), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};

	float matrixB[4][1] =
		{
		{ _object->getPosition()->getX() },
		{ _object->getPosition()->getY() },
		{ _object->getPosition()->getZ() },
		{ 1.0f },
		};

	_object->setPosition(handler->multiplyMatrices(matrixA, matrixB));

}

vector<DrawableObject*> *Camera::getTransformedObjects(SDL_Surface * _screen, vector<DrawableObject*> *_objects){

	// Clear screen

	// Convert from object space to world space
	objects = new vector<DrawableObject*>();

	// View plane normal
	Point *n = getViewPlaneNormal();

	// Intermediate orthogonal axis
	Point *up = getUpVector();
	Point *u = getIntermediateOrthogonalAxis(up, n);
	delete up;

	// New y axis
	Point *v = getNewYAxis(n, u);

	// Clone objects and tranform to view space
	for (int i = 0; i < _objects->size(); i++){
		DrawableObject *clonedObj = _objects->at(i)->clone();

		// Translate by the offset of the camera position
		clonedObj->translate(handler, -position->getX(), -position->getY(), -position->getZ());

		// Transform objects into view space
		transformToViewSpace(clonedObj, u, v, n);

		objects->push_back(clonedObj);

	}

	// Do Projection

	
	// Clean up
	delete n;
	delete up;
	delete u;
	delete v;

	// Return obejcts
	return objects;
}

Point *Camera::getViewPlaneNormal(){
	Point direction(lookingAt->getX() - position->getX(), 
					lookingAt->getY() - position->getY(), 
					lookingAt->getZ() - position->getZ());

	float length = sqrt((direction.getX() * direction.getX()) +
						(direction.getY() * direction.getY()) +
						(direction.getZ() * direction.getZ()));

	return new Point(direction.getX() / length, direction.getY() / length, direction.getZ() / length);
}

Camera::~Camera(void)
{
}
