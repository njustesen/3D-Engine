#include "Camera.h"
#include "Character.h"
#include "main.h"

Camera::Camera(void)
{
}

Camera::Camera(int xFocus, int yFocus)
{
	x = xFocus;
	y = yFocus;
}

void Camera::move(int ticks, Character * character){
	if (character->getX() > x){
		x += (character->getX() - x) / max(1,(CAMERA_DELAY/ticks));
	}
	if (character->getX() < x){
		x += (character->getX() - x) / max(1,(CAMERA_DELAY/ticks));
	}
	if (character->getY() > y){
		y += (character->getY() - y) / max(1,(CAMERA_DELAY/ticks));
	}
	if (character->getY() < y){
		y += (character->getY() - y) / max(1,(CAMERA_DELAY/ticks));
	}
}

int Camera::getX(){
	return x;
}

int Camera::getY(){
	return y;
}

Camera::~Camera(void)
{
}
