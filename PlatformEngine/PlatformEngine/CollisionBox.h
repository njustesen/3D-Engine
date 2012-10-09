#include "Point2D.h"
#include <vector>
using namespace std;

#pragma once
class CollisionBox
{
private:
	vector<Point2D*> * bottomPoints;
	vector<Point2D*> * topPoints;
	vector<Point2D*> * rightPoints;
	vector<Point2D*> * leftPoints;
	int width;
	int height;
public:
	vector<Point2D*> * getBottomPoints();
	vector<Point2D*> * getTopPoints();
	vector<Point2D*> * getRightPoints();
	vector<Point2D*> * getLeftPoints();
	int getWidth();
	int getHeight();
	CollisionBox(vector<Point2D*> * bottom, vector<Point2D*> * top, vector<Point2D*> * left, vector<Point2D*> * right, int w, int h);
	CollisionBox(void);
	~CollisionBox(void);
};

