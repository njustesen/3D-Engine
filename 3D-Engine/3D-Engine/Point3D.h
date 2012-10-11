#pragma once
class Point3D
{
private:
	float x;
	float y;
	float z;
public:
	Point3D(float _x, float _y, float _z);
	Point3D();
	float getX();
	float getY();
	float getZ();
	void setX(float _x);
	void setY(float _y);
	void setZ(float _z);
	~Point3D(void);
};

