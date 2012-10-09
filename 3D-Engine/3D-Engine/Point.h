#pragma once
class Point
{
private:
	float x;
	float y;
	float z;
public:
	Point(float _x, float _y, float _z);
	Point();
	float getX();
	float getY();
	float getZ();
	void setX(float _x);
	void setY(float _y);
	void setZ(float _z);
	~Point(void);
};

