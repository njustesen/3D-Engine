#pragma once
#include "Point3D.h"
#include "SDL.h"
#include <vector>
#include "DrawableObject.h"

class Camera
{
private:
	Point3D *position;
	Point3D *lookingAt;
	float far;
	float near;
	float horizonalViewAngle;
public:
	Point3D *getPosition();
	Point3D *getLookingAt();
	void setPosition(Point3D *_Point3D);
	void setLookingAt(Point3D *_Point3D);
	Point3D *getIntermediateOrthogonalAxis();
	Point3D *getViewPlaneNormal();
	Point3D *getNewYAxis();
	Point3D *getUpVector();
	float getFar();
	float getNear();
	float getHorizontalViewAngle();
	Camera(Point3D *_position, Point3D *_lookingAt, float _horizonalViewAngle);
	~Camera(void);
};

