#pragma once
#include "gameobject.h"
class Fireball : public GameObject {

private:
	int timeAlive;
public:
	void act(int ticks);
	void setupAnimations();
	Fireball(int xpos, int ypos, double xspeed, double yspeed, SDL_Surface * image);
	~Fireball(void);
};

