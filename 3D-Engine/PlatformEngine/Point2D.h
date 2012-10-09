#pragma once
class Point2D
{
private: 
	int x;
	int y;
public:
	int getX();
	int getY();
	void setX(int xpos);
	void setY(int ypos);
	Point2D(void);
	Point2D(int x, int y);
	~Point2D(void);
};

