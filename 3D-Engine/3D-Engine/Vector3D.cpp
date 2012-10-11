#include "Vector3D.h"

Vector3D::Vector3D(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
}

Vector3D::Vector3D(){
	x = 0;
	y = 0;
	z = 0;
}

float Vector3D::getX(){
	return x;
}

float Vector3D::getY(){
	return y;
}

float Vector3D::getZ(){
	return z;
}

void Vector3D::setX(float _x){
	x = _x;
}

void Vector3D::setY(float _y){
	y = _y;
}

void Vector3D::setZ(float _z){
	z = _z;
}


Vector3D::~Vector3D(void)
{
}
