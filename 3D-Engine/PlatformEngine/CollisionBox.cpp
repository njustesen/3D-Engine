#include "CollisionBox.h"
#include "Point2D.h"
#include <vector>
using namespace std;

CollisionBox::CollisionBox(void)
{
}

CollisionBox::CollisionBox(	vector<Point2D*> * bottom, 
							vector<Point2D*> * top, 
							vector<Point2D*> * left, 
							vector<Point2D*> * right, 
							int w, 
							int h){

	bottomPoints = bottom;
	topPoints = top;
	leftPoints = left;
	rightPoints = right;
	width = w;
	height = h;
}
	
vector<Point2D*> * CollisionBox::getBottomPoints(){
	return bottomPoints;
}


vector<Point2D*> * CollisionBox::getTopPoints(){
	return topPoints;
}

vector<Point2D*> * CollisionBox::getRightPoints(){
	return rightPoints;
}

vector<Point2D*> * CollisionBox::getLeftPoints(){
	return leftPoints;
}

int  CollisionBox::getWidth(){
	return width;
}

int  CollisionBox::getHeight(){
	return height;
}

CollisionBox::~CollisionBox(void)
{
}
