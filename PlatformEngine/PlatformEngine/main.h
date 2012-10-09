#include "MapController.h"
#include "Sprite.h"
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include <iostream>
#include <fstream>
using namespace std;

const extern int SCREEN_WIDTH;
const extern int SCREEN_HEIGHT;
const extern int SCREEN_BPP;
const extern int LEVEL_HEIGHT;
const extern int LEVEL_WIDTH;
const extern int TILE_SIZE;
const extern int CAMERA_DELAY;
const extern float CHARACTER_JUMP_POWER;
const extern int MONSTER_WIDTH;
const extern int MONSTER_HEIGHT;
const extern double MONSTER_SPEED;
const extern int MONSTER_RATE_OF_FIRE;
const extern int FIREBALL_TIME_ALIVE;
const extern int FIREBALL_WIDTH;
const extern int FIREBALL_HEIGHT;

void monsterFire(int x, int y, string direction);
SDL_Surface *loadImage(std::string filename);