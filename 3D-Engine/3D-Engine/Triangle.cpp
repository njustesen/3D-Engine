#include "Triangle.h"
#include "Point.h"

Triangle::Triangle(Point *_a, Point *_b, Point *_c){
	a = _a;
	b = _b;
	c = _c;
}

Triangle::Triangle(){

}

Point *Triangle::getA(){
	return a;
}

Point *Triangle::getB(){
	return b;
}

Point *Triangle::getC(){
	return c;
}

void Triangle::setA(Point *_p){
	a = _p;
}

void Triangle::setB(Point *_p){
	b = _p;
}

void Triangle::setC(Point *_p){
	c = _p;
}

Triangle::~Triangle(void)
{
}
