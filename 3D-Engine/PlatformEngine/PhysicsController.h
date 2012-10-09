#include "Character.h"
#include "Level.h"
#include <string>
#include <vector>
using namespace std;
#pragma once
class PhysicsController
{
private: 
	Level * level;
	Character * character;
	vector<GameObject*> * gameObjects;
	bool charOnGround;
	double round(double number);
	bool isSolid(int tile, int x, int y, string dir);
	bool isDeadly(int tile, string dir);
	double checkDownwards(GameObject * object, int x, int y, double moveX, double moveY);
	double checkUpwards(GameObject * object, int x, int y, double moveX, double moveY);
	double checkRight(GameObject * object, int x, int y, double moveX, double moveY);
	double checkLeft(GameObject * object, int x, int y, double moveX, double moveY);
	bool isSolidRightStairs(int tile, int x, int y);
	bool isSolidLeftStairs(int tile, int x, int y);
	double getGravitationalAcceleration(int ticks);
	int correctYPosition(int x, int y, int mapValue);
	void checkFireballCollision();
public:
	void gravity(int ticks);
	void move();
	PhysicsController(Character * chara, vector<GameObject*> * objects, Level * lv);
	PhysicsController(void);
	~PhysicsController(void);
};

