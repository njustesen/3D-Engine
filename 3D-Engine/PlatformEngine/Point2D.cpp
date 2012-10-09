#include "Point2D.h"

Point2D::Point2D(void)
{
	x = 0;
	y = 0;
}

Point2D::Point2D(int xpos, int ypos)
{
	x = xpos;
	y = ypos;
}

void Point2D::setX(int xpos){
	x = xpos;
}

void Point2D::setY(int ypos){
	y = ypos;
}

int Point2D::getX(){
	return x;
}

int Point2D::getY(){
	return y;
}

Point2D::~Point2D(void)
{
}
