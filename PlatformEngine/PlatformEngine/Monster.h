#include "GameObject.h"

#pragma once
class Monster: public GameObject
{
private:
	string direction;
	int timeSinceLastAttack;
public:
	void act(int ticks);
	void setupAnimations();
	string getDirection();
	Monster(int xpos, int ypos, string dir);
	~Monster(void);
};

