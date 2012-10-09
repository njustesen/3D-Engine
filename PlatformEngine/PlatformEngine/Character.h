#include "GameObject.h"
using namespace std;

#pragma once
class Character: public GameObject
{
private: 

public:
	void act(int ticks);
	void setupAnimations();
	Character(int xpos, int ypos, int w, int h, double spd, double bounce);
	~Character(void);
};

