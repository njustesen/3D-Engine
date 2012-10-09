#include <vector>
#include "Point.h"

#pragma once
class Triangle
{
private:
	Point *a;
	Point *b;
	Point *c;
public:
	Triangle(Point *_a, Point *_b, Point *_c);
	Triangle();
	Point *getA();
	Point *getB();
	Point *getC();
	void setA(Point *_p);
	void setB(Point *_p);
	void setC(Point *_p);
	~Triangle(void);
};

