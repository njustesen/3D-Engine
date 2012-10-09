#include "Character.h"
#pragma once
class Camera
{
private:
	int x;
	int y;
public:
	int getX();
	int getY();
	void move(int ticks, Character * character);
	Camera(void);
	Camera(int xFocus, int yFocus);
	~Camera(void);
};

