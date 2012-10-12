#include "Point3D.h"
#include "SDL.h"
#include <vector>
#include "DrawableObject.h"

#pragma once
class Camera
{
private:
	Point3D *position;
	Point3D *lookingAt;
	TransformHandler *handler;
	Point3D *getViewPlaneNormal();
	Point3D *getUpVector();
	Point3D *getIntermediateOrthogonalAxis(Point3D *_up, Point3D *_n);
	Point3D *getNewYAxis(Point3D *_n, Point3D *_u);
	void transformToViewSpace(DrawableObject *_object, Point3D *_u, Point3D *_v, Point3D *_n);
public:
	Point3D *getPosition();
	Point3D *getLookingAt();
	void setPosition(Point3D *_Point3D);
	void setLookingAt(Point3D *_Point3D);
	vector<DrawableObject*> *getTransformedObjects(SDL_Surface * _screen, vector<DrawableObject*> *_objects);
	Camera(Point3D *_position, Point3D *_lookingAt, TransformHandler *_handler);
	~Camera(void);
};

