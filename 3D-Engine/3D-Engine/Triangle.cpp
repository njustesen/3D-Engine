#include "Triangle.h"
#include "Point3D.h"

Triangle::Triangle(Point3D *_a, Point3D *_b, Point3D *_c){
	a = _a;
	b = _b;
	c = _c;
}

Triangle::Triangle(){

}

Point3D *Triangle::getA(){
	return a;
}

Point3D *Triangle::getB(){
	return b;
}

Point3D *Triangle::getC(){
	return c;
}

void Triangle::setA(Point3D *_p){
	a = _p;
}

void Triangle::setB(Point3D *_p){
	b = _p;
}

void Triangle::setC(Point3D *_p){
	c = _p;
}

Triangle::~Triangle(void)
{
}
