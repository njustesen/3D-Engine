#include "Point3D.h"

Point3D::Point3D(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
}

Point3D::Point3D(){
	x = 0;
	y = 0;
	z = 0;
}

float Point3D::getX(){
	return x;
}

float Point3D::getY(){
	return y;
}

float Point3D::getZ(){
	return z;
}

void Point3D::setX(float _x){
	x = _x;
}

void Point3D::setY(float _y){
	y = _y;
}

void Point3D::setZ(float _z){
	z = _z;
}


Point3D::~Point3D(void)
{
}
