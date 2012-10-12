#include "Camera.h"
#include "Point3D.h"
#include "SDL.h"
#include "main.h"
#include <vector>
#include "DrawableObject.h"

Camera::Camera(Point3D *_position, Point3D *_lookingAt, TransformHandler *_handler){
	position = _position;
	lookingAt = _lookingAt;
	handler = _handler;
}

Point3D *Camera::getPosition(){
	return position;
}

Point3D *Camera::getLookingAt(){
	return lookingAt;
}

void Camera::setLookingAt(Point3D *_Point3D){
	if (lookingAt)
		delete lookingAt;

	lookingAt = _Point3D;
}

void Camera::setPosition(Point3D *_Point3D){
	if (position)
		delete position;

	position = _Point3D;
}

Point3D *Camera::getUpVector(){

	Point3D v(0.0f, 1.0f, 0.0f);

	Point3D right(lookingAt->getY() * v.getZ() - lookingAt->getZ() * v.getY(),
				lookingAt->getZ() * v.getX() - lookingAt->getX() * v.getZ(),
				lookingAt->getX() * v.getY() - lookingAt->getY() * v.getX());

	return new Point3D(	right.getY() * lookingAt->getZ() - right.getZ() * lookingAt->getY(),
						right.getZ() * lookingAt->getX() - right.getX() * lookingAt->getZ(),
						right.getX() * lookingAt->getY() - right.getY() * lookingAt->getX());

}

Point3D *Camera::getViewPlaneNormal(){
	Point3D direction(lookingAt->getX() - position->getX(), 
					lookingAt->getY() - position->getY(), 
					lookingAt->getZ() - position->getZ());

	float length = sqrt((direction.getX() * direction.getX()) +
						(direction.getY() * direction.getY()) +
						(direction.getZ() * direction.getZ()));

	return new Point3D(direction.getX() / length, direction.getY() / length, direction.getZ() / length);
}

Point3D *Camera::getIntermediateOrthogonalAxis(Point3D *_up, Point3D *_n){
	Point3D cross(_up->getY() * _n->getZ() - _up->getZ() * _n->getY(),
				_up->getZ() * _n->getX() - _up->getX() * _n->getZ(),
				_up->getX() * _n->getY() - _up->getY() * _n->getX());

	float length = sqrt((cross.getX() * cross.getX()) +
						(cross.getY() * cross.getY()) +
						(cross.getZ() * cross.getZ()));

	return new Point3D(cross.getX() / length, cross.getY() / length, cross.getZ() / length);

}

Point3D *Camera::getNewYAxis(Point3D *_n, Point3D *_u){
	return new Point3D(	_n->getY() * _u->getZ() - _n->getZ() * _u->getY(),
						_n->getZ() * _u->getX() - _n->getX() * _u->getZ(),
						_n->getX() * _u->getY() - _n->getY() * _u->getX());
}

void Camera::transformToViewSpace(DrawableObject *_object, Point3D *_u, Point3D *_v, Point3D *_n){
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
	
	// Convert from object space to world space
	vector<DrawableObject*> *objects = new vector<DrawableObject*>();

	// View plane normal
	Point3D *n = getViewPlaneNormal();

	// Intermediate orthogonal axis
	Point3D *up = new Point3D(0.0f, 0.1f, 0.0f);
	Point3D *u = getIntermediateOrthogonalAxis(up, n);

	// New y axis
	Point3D *v = getNewYAxis(n, u);

	// Clone objects and tranform to view space
	for (int i = 0; i < _objects->size(); i++){
		DrawableObject *clonedObj = _objects->at(i)->clone();

		// Translate by the offset of the camera position
		clonedObj->translate(handler, -position->getX(), -position->getY(), -position->getZ());

		// Transform objects into view space
		clonedObj->transformToViewSpace(handler, u, v, n);
		//transformToViewSpace(clonedObj, u, v, n);

		// Do Projection
		float near = 1000.0f;
		float far = 2000.0f;
		float height = SCREEN_HEIGHT;
		float width = SCREEN_WIDTH;

		clonedObj->projectToNDC(handler, near, far, height, width);

		objects->push_back(clonedObj);

	}

	// Clean up
	if (n)
		delete n;

	if (up)
		delete up;

	if (u)
		delete u;

	if (v)
		delete v;

	// Return obejcts
	return objects;
}

Camera::~Camera(void)
{
}
