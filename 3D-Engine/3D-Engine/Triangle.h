#pragma once
#include <vector>
#include "Point3D.h"


class Triangle
{
private:
	Point3D *a;
	Point3D *b;
	Point3D *c;
public:
	Triangle(Point3D *_a, Point3D *_b, Point3D *_c);
	Triangle();
	Point3D *getA();
	Point3D *getB();
	Point3D *getC();
	void setA(Point3D *_p);
	void setB(Point3D *_p);
	void setC(Point3D *_p);
	~Triangle(void);
};

