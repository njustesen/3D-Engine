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
	near = 30;
	far = 2000;
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

float Camera::getFar(){
	return far;
}


float Camera::getNear(){
	return near;
}


float Camera::getHorizontalViewAngle(){
	return horizonalViewAngle;
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

Point3D *Camera::getIntermediateOrthogonalAxis(){

	Point3D *up = getUpVector();

	Point3D *n = getViewPlaneNormal();

	Point3D cross(up->getY() * n->getZ() - up->getZ() * n->getY(),
				up->getZ() * n->getX() - up->getX() * n->getZ(),
				up->getX() * n->getY() - up->getY() * n->getX());

	float length = sqrt((cross.getX() * cross.getX()) +
						(cross.getY() * cross.getY()) +
						(cross.getZ() * cross.getZ()));

	return new Point3D(cross.getX() / length, cross.getY() / length, cross.getZ() / length);

}

Point3D *Camera::getNewYAxis(){
	
	Point3D *u = getIntermediateOrthogonalAxis();

	Point3D *n = getViewPlaneNormal();

	return new Point3D(	n->getY() * u->getZ() - n->getZ() * u->getY(),
						n->getZ() * u->getX() - n->getX() * u->getZ(),
						n->getX() * u->getY() - n->getY() * u->getX());
}

Camera::~Camera(void)
{
}
