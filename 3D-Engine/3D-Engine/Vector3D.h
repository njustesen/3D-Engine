#pragma once
class Vector3D
{
private:
	float x;
	float y;
	float z;
public:
	Vector3D(float _x, float _y, float _z);
	Vector3D();
	float getX();
	float getY();
	float getZ();
	void setX(float _x);
	void setY(float _y);
	void setZ(float _z);
	~Vector3D(void);
};

