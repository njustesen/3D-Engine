#include "Point.h"
#include "SDL.h"
#include <vector>
#include "DrawableObject.h"

#pragma once
class Camera
{
private:
	Point *position;
	Point *lookingAt;
	TransformHandler *handler;
	vector<DrawableObject*> *objects;
	Point *getViewPlaneNormal();
	Point *getUpVector();
	Point *getIntermediateOrthogonalAxis(Point *_up, Point *_n);
	Point *getNewYAxis(Point *_n, Point *_u);
	void transformToViewSpace(DrawableObject *_object, Point *_u, Point *_v, Point *_n);
public:
	Point *getPosition();
	Point *getLookingAt();
	void setPosition(Point *_point);
	void setLookingAt(Point *_point);
	vector<DrawableObject*> *getTransformedObjects(SDL_Surface * _screen, vector<DrawableObject*> *_objects);
	Camera(Point *_position, Point *_lookingAt, TransformHandler *_handler);
	~Camera(void);
};

